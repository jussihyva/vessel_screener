package main

import (
	"encoding/json"
	"log"
	"net/http"
	"sync"
	"time"

	"github.com/gorilla/websocket"
	"github.com/jinzhu/gorm"
	_ "github.com/jinzhu/gorm/dialects/sqlite"
)

const (
	// Query from database every X sec
	queryInterval = 1 * time.Second
	// Send messages to client every X sec
	pushInterval = 5 * time.Second
	// Query messages newer than
	timeAgo = 30 * time.Second
)

var upgrader = websocket.Upgrader{
	ReadBufferSize:  4096,
	WriteBufferSize: 4096,
}

type server struct {
	err          error
	db           *gorm.DB
	messages     []Message
	jsonResponse []byte
	mu           sync.Mutex
}

// Update data every nth second
func (s *server) updateData() {
	ticker := time.NewTicker(queryInterval)
	// NOTE: How about closing ticker channnel, is it needed?
	defer ticker.Stop()

	for range ticker.C {
		since := time.Now().Add(-(timeAgo))
		s.db.Where("timestamp > ?", since).Order("timestamp desc").Select("id, mmsi, name, lat, lon, timestamp").Find(&s.messages)
		// Because response is same for every client we can create it here
		s.createResponse()
	}
}

func (s *server) createResponse() {
	s.mu.Lock()
	s.jsonResponse, s.err = json.Marshal(s.messages)
	if s.err != nil {
		log.Println(s.err)
		s.jsonResponse = []byte("{}")
	}
	s.mu.Unlock()
}

func (s *server) wsHandle(w http.ResponseWriter, r *http.Request) {
	ws, err := upgradeConnection(w, r)
	if err != nil {
		log.Println(err)
		return
	}
	defer ws.Close()
	s.writeResponse(ws)
}

func upgradeConnection(w http.ResponseWriter, r *http.Request) (*websocket.Conn, error) {
	upgrader.CheckOrigin = func(r *http.Request) bool { return true }
	ws, err := upgrader.Upgrade(w, r, nil)
	if err != nil {
		log.Println(err)
		return ws, err
	}
	return ws, nil
}

func (s *server) writeResponse(conn *websocket.Conn) {
	ticker := time.NewTicker(pushInterval)
	// NOTE: How about closing ticker channnel, is it needed?
	defer ticker.Stop()

	// Write first message without waiting
	if err := s.sendTextMessage(conn); err != nil {
		return
	}
	for t := range ticker.C {
		log.Printf("%+v\n", t)
		if err := s.sendTextMessage(conn); err != nil {
			return
		}
	}
}

func (s *server) sendTextMessage(conn *websocket.Conn) error {
	s.mu.Lock()
	err := conn.WriteMessage(websocket.TextMessage, s.jsonResponse)
	s.mu.Unlock()
	if err != nil {
		log.Println(err)
		return err
	}
	return nil
}

func newServer() *server {
	var err error
	s := &server{jsonResponse: []byte("{}")}
	s.db, err = gorm.Open("sqlite3", "../data.db")
	if err != nil {
		log.Fatal(err)
	}
	return s
}

func (s *server) start(serveStatic bool) {
	defer s.db.Close()
	s.db.AutoMigrate(&Message{})
	go s.updateData()

	http.HandleFunc("/ws", s.wsHandle)
	if serveStatic == true {
		http.Handle("/", http.FileServer(http.Dir("./static")))
	}
	if err := http.ListenAndServe(":8001", nil); err != nil {
		log.Fatal(err)
	}
}

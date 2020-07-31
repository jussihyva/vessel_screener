package main

import (
	"encoding/json"
	"log"
	"net/http"
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
	timeAgo = 10 * time.Second
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
}

// Update data every nth second
func (s *server) updateData() {
	ticker := time.NewTicker(queryInterval)
	for range ticker.C {
		since := time.Now().Add(-(timeAgo))
		s.db.Where("timestamp > ?", since).Order("timestamp desc").Select("id, mmsi, name, timestamp").Find(&s.messages)
		// Because response is same for every client we can create it here
		s.createResponse()
	}
}

func (s *server) createResponse() {
	s.jsonResponse, s.err = json.Marshal(s.messages)
	if s.err != nil {
		log.Println(s.err)
		s.jsonResponse = []byte("{}")
	}
}

func (s *server) wsHandle(w http.ResponseWriter, r *http.Request) {
	ws, err := upgradeConnection(w, r)
	if err != nil {
		log.Println(err)
	}
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
	for t := range ticker.C {
		log.Printf("%+v\n", t)
		err := conn.WriteMessage(websocket.TextMessage, s.jsonResponse)
		if err != nil {
			log.Println(err)
			return
		}
	}
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

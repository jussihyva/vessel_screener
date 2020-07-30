package main

import (
	"fmt"
	"net/http"
	"strconv"
	"time"

	"github.com/gorilla/websocket"
)

var upgrader = websocket.Upgrader{
	ReadBufferSize:  1024,
	WriteBufferSize: 1024,
}

// Upgrade HTTP-request
func Upgrade(w http.ResponseWriter, r *http.Request) (*websocket.Conn, error) {
	upgrader.CheckOrigin = func(r *http.Request) bool { return true }
	ws, err := upgrader.Upgrade(w, r, nil)
	if err != nil {
		fmt.Println(err)
		return ws, err
	}
	return ws, nil
}

// Writer ...
func (s *server) Writer(conn *websocket.Conn) {
	ticker := time.NewTicker(pushInterval)
	for t := range ticker.C {
		fmt.Printf("counter: [%d] %+v\n", s.counter, t)
		err := conn.WriteMessage(websocket.TextMessage, []byte(strconv.Itoa(s.counter)))
		if err != nil {
			fmt.Println(err)
			return
		}
	}
}

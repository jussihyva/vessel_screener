package main

import (
	"fmt"
	"net/http"
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
		fmt.Printf("%+v\n", t)
		err := conn.WriteMessage(websocket.TextMessage, s.jsonResponse)
		if err != nil {
			fmt.Println(err)
			return
		}
	}
}

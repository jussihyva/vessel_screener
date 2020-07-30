package main

import (
	"fmt"
	"net/http"
	"time"
)

const (
	updateInterval = 1 * time.Second
	pushInterval   = 5 * time.Second
)

type server struct {
	// Simulate data, this will be *DB
	counter int
}

// Simulate constantly changing data
func (server *server) updateData() {
	ticker := time.NewTicker(updateInterval)
	for range ticker.C {
		// Not safe
		server.counter++
		if server.counter >= 1000 {
			server.counter = 0
		}
	}
}

func (server *server) wsHandle(w http.ResponseWriter, r *http.Request) {
	ws, err := Upgrade(w, r)
	if err != nil {
		fmt.Println(err)
	}
	server.Writer(ws)
}

func main() {
	var s = &server{counter: 0}
	go s.updateData()

	http.HandleFunc("/ws", s.wsHandle)
	http.Handle("/", http.FileServer(http.Dir("./static")))

	if err := http.ListenAndServe(":8000", nil); err != nil {
		fmt.Println(err)
		return
	}
}

package main

import (
	"flag"
)

func main() {
	serveStatic := flag.Bool("static", false, "Serve static folder also")
	flag.Parse()

	s := newServer()
	s.start(*serveStatic)
}

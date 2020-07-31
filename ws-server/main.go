package main

import (
	"flag"

	_ "github.com/jinzhu/gorm/dialects/sqlite"
)

func main() {
	serveStatic := flag.Bool("static", false, "Serve static folder also")
	flag.Parse()

	s := newServer()
	s.start(*serveStatic)
}

package main

import "time"

// TODO: Add all fields
// [{'AIS': {'MMSI': 230985650, 'TIMESTAMP': '2020-07-30 16:35:25 UTC', 'LATITUDE': 60.46008, 'LONGITUDE': 21.91846, 'COURSE': 296.0, 'SPEED': 0.2, 'HEADING': 68, 'NAVSTAT': 5, 'IMO': 0, 'NAME': 'OSMERUS', 'CALLSIGN': 'OH5332', 'TYPE': 30, 'A': 5, 'B': 10, 'C': 4, 'D': 1, 'DRAUGHT': 3.0, 'DESTINATION': 'MERIMASKU', 'ETA_AIS': '04-28 15:30', 'ETA': '2020-04-28 15:30:00', 'SRC': 'TER', 'ZONE': 'Baltic Sea', 'ECA': True}},

// Message struct
type Message struct {
	ID        int       `json:"id"`
	Mmsi      int       `json:"mmsi"`
	Timestamp time.Time `json:"timestamp"`
	Name      string    `json:"name"`
	Lat       float64   `json:"lat"`
	Lon       float64   `json:"lon"`
}

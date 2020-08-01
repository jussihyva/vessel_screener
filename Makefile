all: build run-ws

build:
	cd ws-server && go build -race -o vessel-server

seed:
	rm data.db
	pipenv run ./scripts/seed_db.py
.PHONY: seed

server:
	cd ws-server && ./vessel-server -static
.PHONY: server

server-python:
	cd server && pipenv run uvicorn main:app --reload --host 0.0.0.0 --port 8000
.PHONY: server-python

open:
	firefox -devtools http://localhost:8001
.PHONY: open

open-python:
	firefox -devtools http://localhost:8000
.PHONY: open-python

run-ws: build
	make -j 3 seed server open
.PHONY: run-ws

run-python: build
	make -j 4 seed server-python server open-python
.PHONY: run-python

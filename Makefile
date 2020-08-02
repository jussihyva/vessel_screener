
all: build-ws

#==============================================================================
# DECODER
#==============================================================================

build-decoder:
	make -C decoder
.PHONY: build-decoder

seed-decoder: build-decoder
	cat assets/logs/new_format.log | ./decoder/aivdm
.PHONY: seed-decoder

#==============================================================================
# WEBSOCKET
#==============================================================================

build-ws:
	cd ws-server && go build -race -o vessel-server

seed-ws:
	rm data.db
	pipenv run ./scripts/seed_db.py
.PHONY: seed-ws

run-ws: build-ws
	cd ws-server && ./vessel-server -static
.PHONY: run-ws

open-ws:
	firefox -devtools http://localhost:8001
.PHONY: open-ws

start-ws: build-ws
	make -j 3 seed-ws run-ws open-ws
.PHONY: start-ws

#==============================================================================
# HTTP
#==============================================================================

run-http:
	cd server && pipenv run uvicorn main:app \
	--reload --host 0.0.0.0 --port 8000
.PHONY: run-http

open-http:
	firefox -devtools http://localhost:8000
.PHONY: open-http

start-all: build-ws
	make -j 4 seed-ws run-http run-ws open-http
.PHONY: start-all

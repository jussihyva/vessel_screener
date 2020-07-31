all: build

build:
	cd ws-server && go build -o vessel-server

seed:
	rm data.db
	pipenv run ./scripts/seed_db.py
.PHONY: seed

server:
	cd ws-server && ./vessel-server -static
.PHONY: server

run: build
	make -j 2 seed server
.PHONY: run

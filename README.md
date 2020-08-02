<h1 align="center">
	Vessel Screener
</h1>

<p align="center">
	<br>
	<img width=400 src="assets/images/diagram.png">
</p>

### Development Setup

Clone with

```
git clone --recurse-submodules -j8 git@github.com:jussihyva/vessel_screener.git
```

#### Pipenv

Install pipenv

`pip install --user pipenv`

Install dependencies

`pipenv install`

Activate it

`pipenv shell`


#### Run

##### Makefile

Test websocket server with faked realtime data

`make`

Run python server with sockets and faked realtime data

`make run-python`

##### Manual

Fake getting realtime data

```sh
$> cd scripts
$> ./seed_db.py
```

Start a websocket server in a new terminal window
```sh
$> go build
$> ./vessel-server
```
Goto http://localhost:8001 (Try it with multiple browsers)

#### Node

`npm install`

#### Scripts
Fetch data form real API

`./fetch.py <url> > ../realtime.log`

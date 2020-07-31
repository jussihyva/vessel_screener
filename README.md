## Good Name For Project Needed
> Includes AIVDM Decoder, Couple servers, Scripts & Front-end

### Development Setup

Clone with

```
git clone --recurse-submodules -j8 git@github.com:jussihyva/aivdm_decoder.git
```

#### Pipenv

Install pipenv

`pip install --user pipenv`

Install dependencies

`pipenv install`

Activate it

`pipenv shell`


#### Run
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
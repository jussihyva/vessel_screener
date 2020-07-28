## Shipit
> Includes AIVDM Decoder & Vessel screener

### Development Setup

#### Python

Install pipenv

`pip install --user pipenv`

Install dependencies

`pipenv install`

Activate it

`pipenv shell`

Fake data

`cat test/new_ais_data_format.log | ./aivdm`

Run server alone

`uvicorn main:app --reload --host 0.0.0.0 --port 8000`

Fetching data with

`./fetch.py <url> > ../realtime.log`

#### Node

`npm install`
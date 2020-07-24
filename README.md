## Shipit
> Includes AIVDM Decoder, Server & Web UI

### Development Setup
Install pipenv

`pip install --user pipenv`

Install dependencies

`pipenv install`

Activate it

`pipenv shell`

Run server alone

`uvicorn main:app --reload --host 0.0.0.0 --port 8000`
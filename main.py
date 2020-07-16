import models
import yfinance
from country import country_name
from fastapi import FastAPI, Request, Depends, BackgroundTasks
from fastapi.templating import Jinja2Templates
from database import SessionLocal, engine
from sqlalchemy.orm import Session
from pydantic import BaseModel
from models import Country

app = FastAPI()

models.Base.metadata.create_all(bind=engine)

templates = Jinja2Templates(directory="templates")

class CountryRequest(BaseModel):
    symbol: str
    timestamp: int

class TableRequest(BaseModel):
    timestamp: int

def get_db():
    try:
        db = SessionLocal()
        yield db
    finally:
        db.close()

@app.get("/")
def home(request: Request, db: Session = Depends(get_db)):
    """
    Displays country code of vessels in The Aura river at Turku.
    """

    country_list = db.query(Country).all()
    for country in country_list:
        if country.country == "-":
            country.country = country_name[country.mmsi_mid]
            db.add(country)
            db.commit()
    
    return templates.TemplateResponse("home.html",
    {
        "request": request,
        "country": country_list
    })

@app.get("/table")
def home(request: Request, db: Session = Depends(get_db)):
    """
    Displays country code of vessels in The Aura river at Turku.
    """

    timestamp = int(request.query_params["timestamp"])
    country_list = db.query(Country).filter(Country.timestamp > int(timestamp))
    for country in country_list:
        print(timestamp)
        print(country.timestamp)
        if country.country == "-":
            country.country = country_name[country.mmsi_mid]
            db.add(country)
            db.commit()
    
    return templates.TemplateResponse("table.html",
    {
        "request": request,
        "country": country_list
    })

def fetch_country_data(mmsi_mid: int):
    db = SessionLocal()
    country = db.query(Country).filter(Country.mmsi_mid == mmsi_mid).first()
    country.country = country_name[mmsi_mid]
    db.add(country)
    db.commit()

@app.post("/country")
async def create_country(country_request: CountryRequest, backround_task: BackgroundTasks, db: Session = Depends(get_db)):
    """
    Updateas a vellel related information in The Aura river at Turku.
    """
    country = db.query(Country).filter(Country.mmsi_mid == country_request.symbol).first()
    if (country == None):
        country = Country()
        country.mmsi_mid = country_request.symbol
        country.timestamp = country_request.timestamp
        country.comment = "Only for test. This is NOT correct information."
        db.add(country)
        db.commit()
        backround_task.add_task(fetch_country_data, country.mmsi_mid)
    else:
        print(country_request.timestamp)
        country.timestamp = country_request.timestamp
        db.add(country)
        db.commit()

    return {
        "code": "success",
        "message": "country created"
    }

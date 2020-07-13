import models
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

def get_db():
    try:
        db = SessionLocal()
        yield db
    finally:
        db.close()

@app.get("/")
def home(request: Request):
    """
    Displays country code of vessels in The Aura river at Turku.
    """
    return templates.TemplateResponse("home.html",
    {
        "request": request,
        "mmsi": "230xxxxxx"
    })

def fetch_country_data(mmsi_mid: int):
    db = SessionLocal()
    country = db.query(Country).filter(Country.mmsi_mid == mmsi_mid).first()

    country.country = "Finland"
    db.add(country)
    db.commit()

@app.post("/country")
async def create_country(country_request: CountryRequest, backround_task: BackgroundTasks, db: Session = Depends(get_db)):
    """
    Updateas a vellel related information in The Aura river at Turku.
    """

    country = Country()
    country.mmsi_mid = country_request.symbol

    db.add(country)
    db.commit()

    backround_task.add_task(fetch_country_data, country.mmsi_mid)

    return {
        "code": "success",
        "message": "stock created"
    }

import models
from fastapi import FastAPI, Request, Depends, BackgroundTasks
from fastapi.templating import Jinja2Templates
from database import SessionLocal, engine
from sqlalchemy.orm import Session
from pydantic import BaseModel
from fastapi.staticfiles import StaticFiles
from main_mmsi import *
from main_country import *

app = FastAPI()

app.mount("/static", StaticFiles(directory="static"), name="static")

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

    country_list = []
    statistic = Statistic(message_1 = 0, message_2 = 0, message_3 = 0)
    return templates.TemplateResponse("home.html",
    {
        "request": request,
        "country": country_list,
        "statistic": statistic
    })

@app.get("/table_country")
def table_country(request: Request, db: Session = Depends(get_db)):
    """
    Displays country code of vessels in The Aura river at Turku.
    """

    response = get_country_table(request, db)
    return(response)

@app.get("/table_message_statistics")
def table_country(request: Request, db: Session = Depends(get_db)):
    """
    Displays country code of vessels in The Aura river at Turku.
    """

    response = get_message_statistics_table(request, db)
    return(response)

@app.get("/table_mmsi")
def table_mmsi(request: Request, db: Session = Depends(get_db)):
    """
    Displays country code of vessels in The Aura river at Turku.
    """

    response = get_mmsi_table(request, db)
    return(response)

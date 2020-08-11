from fastapi.templating import Jinja2Templates
from country import country_name
from models import Country, Message_3
from pydantic import BaseModel
from sqlalchemy import func

templates = Jinja2Templates(directory="templates")

class Country_data(BaseModel):
    mid: int
    num_of_mmsi: int
    country: str

def get_country_list(request, db):
    country_data_list : Country_data = []
    timestamp = int(request.query_params["timestamp"])
    country_list = db.query(Country).filter(Country.timestamp > int(timestamp))
    message_3_list = db.query(Message_3.mid, func.count(Message_3.mid)).filter(Message_3.ais_dispatcher_time > int(timestamp)).group_by(Message_3.mid)
    print(message_3_list)
    for message in message_3_list:
        message_data = Country_data(mid = message.mid, num_of_mmsi = message[1], country = country_name[message.mid])
        country_data_list.append(message_data)
        print(message_data)
    for country in country_list:
        if country.country in ["-", None]:
            country.country = country_name[country.mmsi_mid]
            db.add(country)
            db.commit()
    return templates.TemplateResponse("table_country.html",
    {
        "request": request,
        "country": country_data_list
    })

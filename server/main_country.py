from fastapi.templating import Jinja2Templates
from country import country_name_list
from models import Country, Message_1, Message_2, Message_3
from pydantic import BaseModel
from sqlalchemy import func, distinct

templates = Jinja2Templates(directory="templates")

class Country_data(BaseModel):
    mid: int
    num_of_mmsi: int
    country_name: str

def get_country_table(request, db):
    country_data_list : Country_data = []
    timestamp = int(request.query_params["timestamp"])
    num_of_message_1 = db.query(func.count(Message_1.mmsi)).filter(Message_1.ais_dispatcher_time > \
        int(timestamp))[0][0]
    num_of_message_2 = db.query(func.count(Message_2.mmsi)).filter(Message_2.ais_dispatcher_time > \
        int(timestamp))[0][0]
    num_of_message_3 = db.query(func.count(Message_3.mmsi)).filter(Message_3.ais_dispatcher_time > \
        int(timestamp))[0][0]
    print(num_of_message_1)
    print(num_of_message_2)
    print(num_of_message_3)
    message_3_list = db.query(Message_3.mid, \
        func.count(distinct(Message_3.mmsi))).filter(Message_3.ais_dispatcher_time > \
        int(timestamp)).group_by(Message_3.mid)
    for message in message_3_list:
        country_data = Country_data(mid = message.mid, num_of_mmsi = message[1], \
                        country_name = country_name_list[message.mid])
        country_data_list.append(country_data)
    return templates.TemplateResponse("table_country.html",
    {
        "request": request,
        "country_data_list": country_data_list
    })

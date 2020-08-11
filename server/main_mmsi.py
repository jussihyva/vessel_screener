from fastapi.templating import Jinja2Templates
from country import country_name_list
from models import Country

templates = Jinja2Templates(directory="templates")

def get_mmsi_table(request, db):
    timestamp = int(request.query_params["timestamp"])
    country_list = db.query(Country).filter(Country.timestamp > int(timestamp))
    for country in country_list:
        if country.country == "-":
            country.country = country_name_list[country.mmsi_mid]
            db.add(country)
            db.commit()
    return templates.TemplateResponse("table_mmsi.html",
    {
        "request": request,
        "country": country_list
    })

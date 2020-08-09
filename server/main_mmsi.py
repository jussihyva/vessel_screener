from country import country_name
from models import Country

def get_mmsi_list(request, db):
    timestamp = int(request.query_params["timestamp"])
    country_list = db.query(Country).filter(Country.timestamp > int(timestamp))
    for country in country_list:
        if country.country == "-":
            country.country = country_name[country.mmsi_mid]
            db.add(country)
            db.commit()
    return(country_list)

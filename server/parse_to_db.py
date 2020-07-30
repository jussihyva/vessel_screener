#!/usr/bin/env python

import json
import ast
from sqlalchemy import create_engine, Table, Column, Integer, String, MetaData
engine = create_engine("sqlite:///country.db", echo = True)
meta = MetaData()

messages = Table(
	"messages", meta,
	Column("id", Integer, primary_key = True),
	Column("timestamp", String),
)
meta.create_all(engine)
conn = engine.connect()
lines = (line.rstrip('\n') for line in open("../assets/external_json_small.log"))

#conn.execute(students.insert(), [
#   {'name':'Rajiv', 'lastname' : 'Khanna'},
#   {'name':'Komal','lastname' : 'Bhandari'},
#   {'name':'Abdul','lastname' : 'Sattar'},
#   {'name':'Priya','lastname' : 'Rajhans'},
#])

#[{'AIS': {'MMSI': 230985650, 'TIMESTAMP': '2020-07-30 16:35:25 UTC', 'LATITUDE': 60.46008, 'LONGITUDE': 21.91846, 'COURSE': 296.0, 'SPEED': 0.2, 'HEADING': 68, 'NAVSTAT': 5, 'IMO': 0, 'NAME': 'OSMERUS', 'CALLSIGN': 'OH5332', 'TYPE': 30, 'A': 5, 'B': 10, 'C': 4, 'D': 1, 'DRAUGHT': 3.0, 'DESTINATION': 'MERIMASKU', 'ETA_AIS': '04-28 15:30', 'ETA': '2020-04-28 15:30:00', 'SRC': 'TER', 'ZONE': 'Baltic Sea', 'ECA': True}},

for line in lines:
	if line != "":
		data_list = ast.literal_eval(line)
		for item in data_list:
			# noqa pylint: disable=E1120
			ins = messages.insert().values(timestamp = item["AIS"]["TIMESTAMP"])
			res = conn.execute(ins)
			print(res)

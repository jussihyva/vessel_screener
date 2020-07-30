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

for line in lines:
	if line != "":
		data_list = ast.literal_eval(line)
		for item in data_list:
			# noqa pylint: disable=E1120
			ins = messages.insert().values(timestamp = item["AIS"]["TIMESTAMP"])
			res = conn.execute(ins)
			print(res)

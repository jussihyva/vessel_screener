#!/usr/bin/env python

import json
import ast
import time
import random
import os
from datetime import datetime
from sqlalchemy import create_engine, Table, Column, Integer, String, MetaData, DateTime, Float

# Doesn't matter where script was started
dir_path = os.path.dirname(os.path.realpath(__file__))
DB_PATH = "sqlite:///" + os.path.join(dir_path, "../data.db")
LOG_PATH = os.path.join(dir_path, "../assets/api-logs/small.log")

engine = create_engine(DB_PATH, echo = True)
meta = MetaData()

# TODO: Add all fields. Example:
# [{'AIS': {'MMSI': 230985650, 'TIMESTAMP': '2020-07-30 16:35:25 UTC', 'LATITUDE': 60.46008, 'LONGITUDE': 21.91846, 'COURSE': 296.0, 'SPEED': 0.2, 'HEADING': 68, 'NAVSTAT': 5, 'IMO': 0, 'NAME': 'OSMERUS', 'CALLSIGN': 'OH5332', 'TYPE': 30, 'A': 5, 'B': 10, 'C': 4, 'D': 1, 'DRAUGHT': 3.0, 'DESTINATION': 'MERIMASKU', 'ETA_AIS': '04-28 15:30', 'ETA': '2020-04-28 15:30:00', 'SRC': 'TER', 'ZONE': 'Baltic Sea', 'ECA': True}},
messages = Table(
	"messages", meta,
	Column("id", Integer, primary_key = True),
	Column("mmsi", Integer),
	Column("name", String),
	Column("lat", Float),
	Column("lon", Float),
	Column("timestamp", DateTime),
)

meta.create_all(engine)
conn = engine.connect()
lines = (line.rstrip('\n') for line in open(LOG_PATH))

# TODO: Make this faster
for line in lines:
	if line == "":
		continue
	data_list = ast.literal_eval(line)
	for item in data_list:
		# Real example below, but lets fake timestamp
		# dtime = datetime.strptime(item["AIS"]["TIMESTAMP"], "%Y-%m-%d %H:%M:%S %Z")
		dtime = datetime.now()
		# noqa pylint: disable=E1120
		ins = messages.insert().values(
			timestamp = dtime,
			mmsi = item["AIS"]["MMSI"],
			name = item["AIS"]["NAME"],
			lat = item["AIS"]["LATITUDE"],
			lon = item["AIS"]["LONGITUDE"],
		)
		res = conn.execute(ins)
		# Simulate real data
		time.sleep(random.randint(1, 5))

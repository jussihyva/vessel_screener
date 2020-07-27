#!/usr/bin/env python3

import requests
import time
import sys

INTERVAL = 65

if len(sys.argv) != 2:
	exit("Give one URL as a param")

def fetch_json():
	r = requests.get(sys.argv[1])
	return r.json()

def parse_latest(json_data):
	count = len(json_data)
	# TODO: Handle possible error
	latest = json_data[count - 1]["AIS"]["TIMESTAMP"]
	return latest

while True:
	latest = parse_latest(fetch_json())
	print(latest)
	time.sleep(INTERVAL)

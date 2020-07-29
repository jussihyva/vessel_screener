#!/usr/bin/env python3

import requests
import logging
import time
import sys

INTERVAL = 65

if len(sys.argv) != 2:
	exit("Give one URL as a param")

logging.basicConfig(
    format='%(asctime)s %(levelname)-8s %(message)s',
    level=logging.INFO,
    datefmt='%Y-%m-%d %H:%M:%S'
)

log = logging.getLogger(__name__)
def fetch_json():
	r = requests.get(sys.argv[1])
	return r.json()

while True:
	print(fetch_json())
	print("\n")
	log.info("JSON fetched")
	time.sleep(INTERVAL)

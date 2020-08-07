# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    models.py                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/13 17:49:07 by jkauppi           #+#    #+#              #
#    Updated: 2020/08/06 13:42:10 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

from sqlalchemy import Column, Integer, String, DateTime, Float
from sqlalchemy.sql import func
from database import Base

class Country(Base):
	__tablename__ = "country"

	id = Column(Integer, primary_key=True, index=True)
	mmsi_mid = Column(Integer, unique=True, index=True)
	country = Column(String)
	timestamp = Column(Integer)
	comment = Column(String)

class Message_1(Base):
	__tablename__ = "message_1"

	id = Column(Integer, primary_key=True, index=True)
	decoder_time = Column(Integer, unique=False, index=True)
	ais_dispatcher_time = Column(Integer, unique=False, index=True)
	message_id = Column(Integer)
	repeat_indicator = Column(Integer)
	mmsi = Column(Integer)
	navigational_status = Column(Integer)
	rate_of_turn = Column(Integer)
	speed_over_ground = Column(Float)
	position_accuracy = Column(Integer)
	longitude = Column(Integer)
	latitude = Column(Integer)
	course_over_ground = Column(Integer)
	true_heading = Column(Integer)
	timestamp = Column(Integer)
	special_manoeuvre_indicator = Column(Integer)
	spare = Column(Integer)
	raim_flag = Column(Integer)
	communication_state = Column(Integer)
	dummy = Column(Integer)

class Message_2(Base):
	__tablename__ = "message_2"

	id = Column(Integer, primary_key=True, index=True)
	decoder_time = Column(Integer, unique=False, index=True)
	ais_dispatcher_time = Column(Integer, unique=False, index=True)
	message_id = Column(Integer)
	repeat_indicator = Column(Integer)
	mmsi = Column(Integer)
	navigational_status = Column(Integer)
	rate_of_turn = Column(Integer)
	speed_over_ground = Column(Float)
	position_accuracy = Column(Integer)
	longitude = Column(Integer)
	latitude = Column(Integer)
	course_over_ground = Column(Integer)
	true_heading = Column(Integer)
	timestamp = Column(Integer)
	special_manoeuvre_indicator = Column(Integer)
	spare = Column(Integer)
	raim_flag = Column(Integer)
	communication_state = Column(Integer)
	dummy = Column(Integer)

class Message_3(Base):
	__tablename__ = "message_3"

	id = Column(Integer, primary_key=True, index=True)
	decoder_time = Column(Integer, unique=False, index=True)
	ais_dispatcher_time = Column(Integer, unique=False, index=True)
	message_id = Column(Integer)
	repeat_indicator = Column(Integer)
	mmsi = Column(Integer)
	navigational_status = Column(Integer)
	rate_of_turn = Column(Integer)
	speed_over_ground = Column(Float)
	position_accuracy = Column(Integer)
	longitude = Column(Integer)
	latitude = Column(Integer)
	course_over_ground = Column(Integer)
	true_heading = Column(Integer)
	timestamp = Column(Integer)
	special_manoeuvre_indicator = Column(Integer)
	spare = Column(Integer)
	raim_flag = Column(Integer)
	communication_state = Column(Integer)
	dummy = Column(Integer)

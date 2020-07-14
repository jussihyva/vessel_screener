# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    models.py                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/13 17:49:07 by jkauppi           #+#    #+#              #
#    Updated: 2020/07/14 12:01:51 by jkauppi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

from sqlalchemy import Column, Integer, String
from database import Base

class Country(Base):
	__tablename__ = "country"

	id = Column(Integer, primary_key=True, index=True)
	mmsi_mid = Column(Integer, unique=True, index=True)
	country = Column(String)
	comment = Column(String)

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    models.py                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/13 17:49:07 by jkauppi           #+#    #+#              #
#    Updated: 2020/07/15 07:43:39 by ubuntu           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

from sqlalchemy import Column, Integer, String
from database import Base

class Country(Base):
	__tablename__ = "country"

	id = Column(Integer, primary_key=True, index=True)
	mmsi_mid = Column(Integer, unique=True, index=True)
	country = Column(String)
	timestamp = Column(Integer)
	comment = Column(String)

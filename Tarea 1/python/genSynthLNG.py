#!/usr/bin/env python
# -*- coding: utf-8 -*-

# change format

# Changes the txt ebooks to an accepted format.

# Preprocese los libros que utilizara, de modo que la entrada de sus estructuras
# solo contenga espacios y letras minusculas (elimine saltos de linea, puntuacion,
# lleve todo a minusculas, etc). Para cada libro, construya cada una de las estructuras
# mencionadas, documentando los tiempos de construccion.

import re
import sys
import random

#FILTERPATTERN = re.compile("[^a-zA-ZàèìòùáéíóúÀÈÌÒÙÁÉÍÓÚäëïöüÄËÏÖÜÑñ]")
FILTERPATTERN = re.compile("[^a-zA-Z\ ]")

def process(book):
	a = open(book,"r")
	# my_buffer contains the complete text

	my_buffer = ""
	for line in a:
		my_buffer += line
	a.close()

	# Now remove all things not necesary
	my_string = FILTERPATTERN.split(my_buffer)
	my_string = "".join(my_string)
	#print my_string

	my_string = my_string.lower()

	my_string = re.sub(r"\s+", " ", my_string)
	# no quiero pensar mucho, solo voy a actuar
	diction = my_string.split()
	my_string = ""
	while len(my_string)<1000000:
		my_string += " "
		my_string += diction[random.randint(0,len(diction))]

	b = open("cf-"+book,"w")
	paso = len(my_string)/50
	for i in range(paso):
		b.write(my_string[50*i:(i+1)*50])
	b.write(my_string[50*i:])
	b.close()

if __name__ == '__main__':
	books = sys.argv[1:]
	for book in books:
		process(book)

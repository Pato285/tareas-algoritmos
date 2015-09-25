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

FILTERPATTERN = re.compile("[^a-zA-ZàèìòùáéíóúÀÈÌÒÙÁÉÍÓÚäëïöüÄËÏÖÜÑñ]")

def process(book):
	a = open(book,"r")
	# my_buffer contains the complete text

	my_buffer = ""
	for line in a:
		my_buffer += line
	a.close()

	# Now remove all things not necesary
	my_string = FILTERPATTERN.split(my_buffer)
	my_string = " ".join(my_string)

	my_string = my_string.lower()

	my_string = re.sub(r"\s+", " ", my_string)

	b = open(book,"w")
	paso = len(my_string)/50
	for i in range(paso):
		b.write(my_string[50*i:(i+1)*50])
	b.write(my_string[50*i:])
	b.close()

if __name__ == '__main__':
	books = sys.argv[1:]
	# books = [
	# 	"books/Carrie.txt",
	# 	"books/Clash_of_Kings.txt",
	# 	"books/Dance_with_Dragons.txt",
	# 	"books/Don_Quixote.txt",
	# 	"books/Feast_of_Crows.txt",
	# 	"books/Game_of_Thrones.txt",
	# 	"books/grimms.txt",
	# 	"books/Harry_Potter_and_the_Chamber_of_Secrets.txt",
	# 	"books/Harry_Potter_and_the_Goblet_of_Fire.txt",
	# 	"books/Harry_Potter_and_the_Prisoner_of_Azkaban.txt",
	# 	"books/Harry_Potter_and_the_Sorcerer_s_Stone.txt",
	# 	"books/Hitchhiker_s_Guide_to_the_Galaxy.txt",
	# 	"books/Mostly_Harmless.txt",
	# 	"books/Restaurant_at_the_end_of_the_Universe.txt",
	# 	"books/So_Long_and_Thanks_for_All_The_Fish.txt",
	# 	"books/Star_Wars_A_New_Hope.txt",
	# 	"books/Star_Wars_Revenge_of_the_Jedi.txt",
	# 	"books/Star_Wars_The_Empire_Strikes_Back.txt",
	# 	"books/Storm_of_Swords.txt",
	# 	"books/The_Count_of_Montecristo.txt",
	# 	"books/The_Life_the_Universe_and_Everything.txt"
	# ]

	for book in books:
		process(book)
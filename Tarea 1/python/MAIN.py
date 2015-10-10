from Automaton import *
from Patricia import *
from utils import *
import sys
import time
import random

BUILDTIME_NUMBER_OF_TESTS = 1

def BUILDTIME_PATRICIA(text):
	for i in range(len(text)):
		start = time.clock()
		
		pat = Patricia(text[i])

		end = time.clock()
		print end - start,"\t",
	print ""

def BUILDTIME_AUTOMATA(patterns, alphabets):
	for i in range(len(patterns)):
		start = time.clock()
		for p in patterns[i]:		
			auto = Automaton(p,alphabets[i])
			
		end = time.clock()
		print end - start,"\t",
	print ""

def SEARCH_PATRICIA(text,sample):
	for i in range(len(text)):
		print "text",i
		pat = Patricia(text[i])
		for s in sample[i]:
			start = time.clock()
		
			pat.search(s)

			end = time.clock()
			print end - start

def SEARCH_AUTOMATON(sample,alphabet,text):
	for i in range(len(text)):
		print "text",i
		for s in sample[i]:
			auto = Automaton(s,alphabet[i])

			start = time.clock()
			
			auto.match(text[i])

			end = time.clock()
			print end - start

if __name__ == '__main__':
	if len(sys.argv) == 1:
		booknames = ["books/TESTBOOK.txt"]
	else:
		booknames = sys.argv[1:]
	# cargar libros en memoria
	book = load_books(booknames)
	book_split = [b.split() for b in book]
	# generar alfabetos
	alphabet = get_alphabets(book)

	print "BOOKS\t",
	print booknames

	print "SIZE OF THE ALPHABETS\t",
	print [len(n) for n in alphabet]

	print "SIZE OF THE BOOKS (IN WORDS)\t",
	print [len(b) for b in book_split]

	# escoger N/10 palabras de forma aleatoria
	sample_size = [len(b)/10 for b in book_split]
	sample = [random.sample(book_split[i],sample_size[i]) for i in range(len(booknames))]

	print "SAMPLE SIZE\t",
	print sample_size

	# calcular tiempos de construccion
	# ===== AUTOMATA =====
	print "BUILDTIME AUTOMATA"
	for i in range(BUILDTIME_NUMBER_OF_TESTS): BUILDTIME_AUTOMATA(sample,alphabet)
	# ===== PATRICIA =====
	print "BUILDTIME PATRICIA"
	for i in range(BUILDTIME_NUMBER_OF_TESTS): BUILDTIME_PATRICIA(book_split)

	# encontrar todas las ocurrencias de estas en el texto
	# usando cada una de las estructuras
	# ===== AUTOMATA =====
	print "SEARCH AUTOMATA"
	SEARCH_AUTOMATON(sample,alphabet,book)
	# ===== PATRICIA =====
	print "SEARCH PATRICIA"
	SEARCH_PATRICIA(book_split,sample)
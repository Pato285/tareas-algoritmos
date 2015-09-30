import numpy

sizeofchar = 1 #Byte
numberofbytes = 1 * 1024 * 1024

TCAG = [ord('T'),ord('C'),ord('A'),ord('G')]

def change(char):
	return TCAG[char]

array = numpy.array(map(change,numpy.random.randint(0,4,numberofbytes)),numpy.byte)

f = open('DNA.txt', 'wb')

f.write(array)

f.close()

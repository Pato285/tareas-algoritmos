import numpy

sizeofchar = 1 #Byte
numberofbytes = 2 * 1024 * 1024

TCAG = [ord('T'),ord('C'),ord('A'),ord('G')]

def change(char):
	return TCAG[char]

array = numpy.zeros(numberofbytes/8, [
								("dna", numpy.byte, 8),
								("sp"   , numpy.byte, 1)])

array["dna"] = numpy.array(map(change,numpy.random.randint(0,4,numberofbytes)),numpy.byte).reshape(numberofbytes/8,8)
array["sp"] = ord(" ")

f = open('DNA.txt', 'wb')

f.write(array)

f.close()
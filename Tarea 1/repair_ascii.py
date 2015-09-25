import sys
import re

def findIndex(pattern,string):
	return [(m.start(0), m.end(0)) for m in re.finditer(pattern, string)]

def main(arg):
	a = open(arg,'r')
	buffer = []
	for line in a:
		idxs = findIndex(r'&#.{1,3};',line)
		idxs.reverse()
		repaired = line
		for (i,f) in idxs:
		#	print line[i:f],unichr(int(line[i+2:f-1]))
			repaired = repaired[:i]+chr(int(line[i+2:f-1]))+repaired[f:]
		#print repaired
		buffer.append(repaired)
	a.close()

	a = open(arg,'w')
	for line in buffer:
		a.write(line)
	a.close()

if __name__ == '__main__':
	main(sys.argv[1])
import numpy as np

a = open("results1.csv","r")
automaton = [[],[],[],[],[]]
patricia = [[],[],[],[],[]]
i=-1
text = automaton
for l in a:
	if l.startswith("SEARCH"): text = patricia; i = -1; continue
	if l.startswith("text"): i+=1; continue;
	text[i].append(float(l))
	
a.close()

automaton = map(lambda x: np.array(x),automaton)
patricia = map(lambda x: np.array(x),patricia)

# por cada texto tener promedios de tiempos de busqueda para n=100 hasta 30.000
print "automaton"
print "size\tbook0\tbook1\tbook2\tbook3\tbook4"
for s in xrange(100,26000,500):
	print s,
	for i in xrange(5):
		print np.mean(np.random.choice(automaton[i], size=s, replace=False)),
	print ""

print "patricia"
print "size\tbook0\tbook1\tbook2\tbook3\tbook4"
for s in xrange(100,26000,500):
	print s,
	for i in xrange(5):
		print np.mean(np.random.choice(patricia[i], size=s, replace=False)),
	print ""
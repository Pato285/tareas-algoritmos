import string, random

s = set()
SIZE = 2**8
OUT_SIZE = 2**15

assert len(string.ascii_lowercase)**SIZE >= OUT_SIZE
while len(s)<OUT_SIZE:
    s.add(''.join(random.choice(string.ascii_lowercase) for _ in xrange(SIZE)))

a = open("word_8_15.txt","w")
while len(s)>1:
    l = s.pop()
    a.write(l)
    a.write(" ")
a.write(s.pop())
a.close()

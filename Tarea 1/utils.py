def is_prefix(s1,s2):
	return s1.startswith(s2)

def is_suffix(s1,s2):
	return s1.endswith(s2)

def get_common_prefix(s1,s2):
	minval = min(len(s1),len(s2))
	if minval == 0: return ""
	i = 0
	while i<minval and s1[i]==s2[i]:
		i += 1
	return s1[:i]

def get_common_suffix(s1,s2):
	minval = min(len(s1),len(s2))+1
	if minval == 1: return ""
	i = 1
	while i<minval and s1[-i]==s2[-i]:
		i += 1
	if s1[-i+1]!=s2[-i+1]: return ""
	return s1[-i+1:]

def get_alphabet(text):
	l = list(set(list(text)))
	l.sort()
	return l

class Pointer:
	def __init__(self,obj):
		self.obj = obj

	def get(self):
		return self.obj

	def set(self,obj):
		self.obj = obj

def load_book(filename):
	f = open(filename,'r')
	out = ""
	for line in f: out += line
	return out

def load_books(filenames):
	return [load_book(name) for name in filenames]

def get_alphabets(texts):
	return [get_alphabet(text) for text in texts]
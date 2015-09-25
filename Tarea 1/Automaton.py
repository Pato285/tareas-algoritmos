from utils import *

class Automaton:
	def __init__(self,pattern,alphabet):
		self.transformMatrix = None
		self.transformAlphabet = {k:v for (v,k) in enumerate(alphabet)}
		self.m = 0

		self.computeTransforation(pattern,alphabet)

	def match(self,text):
		n = len(text)
		q = 0
		out = []
		for i in range(0,n):
			q = self.transformation(q,text[i])
			if q == self.m:
				out.append( i-self.m+1 )
		return out

	def computeTransforation(self,pattern,alphabet):
		self.m = len(pattern)

		self.transformMatrix = [[0]*len(alphabet) for h in range(self.m+1)]

		for q in range(0,self.m+1):
			for a in alphabet:
				k = min(self.m,q+1)
				while not is_suffix(pattern[:q]+a,pattern[:k]):
					k -= 1
				self.setTransformation(q,a,k)

	def setTransformation(self,q,a,k):
		i = self.transformAlphabet[a]
		self.transformMatrix[q][i] = k

	def transformation(self,q,a):
		i = self.transformAlphabet[a]
		return self.transformMatrix[q][i]
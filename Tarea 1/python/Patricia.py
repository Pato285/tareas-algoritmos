from utils import *

class Patricia:
	class Leaf:
		def __init__(self,string,idx):
			self.string = string
			self.idx = [idx]

		def search(self,string,aw):
			if self.string==string:
				return self.idx
			else:
				return []

		def insert(self,string,aw,idx):
			if self.string==string:
				self.idx.append(idx)
				return self

			w = string[len(self.string):]
			pn = Patricia.Node()
			pn.nodes[''] = self
			pn.nodes[w] = Patricia.Leaf(string,idx)
			return pn

		def dfs(self,array):
			if self.string == '':
				array.append( "$" )
			else:
				array.append( self.string )

	class Node:
		def __init__(self):
			self.nodes = {}

		def search(self,string,aw):
			arcs = self.nodes.keys()
			lcp = ''
			for ed in arcs:
				lcp = get_common_prefix(ed,aw)
				if lcp != '': break

			if lcp in arcs:
				return self.nodes[lcp].search(string,aw[len(lcp):])
			else:
				return []

		def insert(self,string,aw,idx):
			arcs = self.nodes.keys()
			lcp = ''
			for ed in arcs:
				lcp = get_common_prefix(ed,aw)
				if lcp != '': break

			if lcp in arcs:
				self.nodes[lcp] = self.nodes[lcp].insert(string,aw[len(lcp):],idx)
			elif lcp == '':
				self.nodes[aw] = Patricia.Leaf(string,idx)
			else:
				pn = Patricia.Node()
				pn.nodes[ed[len(lcp):]] = self.nodes[ed]
				pn.nodes[aw[len(lcp):]] = Patricia.Leaf(string,idx)
				self.nodes.pop(ed,None)
				self.nodes[lcp] = pn
			return self

		def dfs(self,array):
			keys = self.nodes.keys()
			keys.sort()

			for word in keys:
				if word == '':
					array.append("$")
				else:
					array.append(word)
				self.nodes[word].dfs(array)

	def __init__(self,st_arr):
		self.root = Patricia.Node()
		for i in range(len(st_arr)):
			self.root.insert(st_arr[i],st_arr[i],i)

	def search(self,string):
		return self.root.search(string,string)

	def dfs(self):
		r = []
		self.root.dfs(r)
		return " ".join(r)

# Sea W = aw string a insertar
# Para todo nodo n=(A), con A un subconjunto de AxN, E conjunto de etiquetas de arcos
# y N el conjunto de nodos.
# Sea LCP(e,s) el Longest Common Prefix, el prefijo comun mas largo
# 
# Sabemos que para un nodo n en N existe a lo mas un LCP(e,W)!='' [1]
# 
# [1] Supongamos que existen dos arcos con LCP!='', significa que existen dos arcos con
# un prefijo comun -> el arbol patricia esta mal construido.
# 
# Algoritmo:
# 
# INSERT_PATRICIA(N,S,W):
# 
# INPUT:
# 		 N - Nodo donde insertar
# 		 S - String a insertar.
# 		 W - Porcion del string no cubierta por el path tomado
# 
# 	Encontrar el mayor LCP entre todos los arcos. e
# 	LCP(e,W)
# 	IF: LCP(e,W) = e
#	  DO: W = ew
# 		  INSERT_PATRICIA(Nodes[e],S,w)
# 	  ELSE: IF: LCP(e,W) = ''
# 			  DO: Nodes[W] = Leaf(S)
# 			  ELSE: n = Nodes[e]
# 					e = LCP(e,W)e'
# 					W = LCP(e,W)w'
# 					DELETE(Nodes[e])
# 					n' = Node()
# 					Link node n' with n with arc e'
# 					Link node m' with Leaf(S) with arc w'
# 					Nodes[LCP(e,W)] = n'
from utils import *
from Automaton import *
from Patricia import *
#from SuffixTree import *

printonOK = False
def TEST(fun,expected,*args):
	res = fun(*args)

	if res == expected:
		if printonOK:
			print "TEST -",fun.__name__,args,"- OK"
	else:
		print "TEST -",fun.__name__,args,"- BAD, got \""+str(res)+"\" expected '"+str(expected)+"'"

print "TEST STARTED"
#============================= GETALPHABET =============================
#printonOK = True
TEST(get_alphabet,[' ','d','e','h','i','n','o','r','s','t','y'],"do or do not there is no try")
TEST(get_alphabet,['\n',' ','a','l']," \nla")
#printonOK = False
#============================ PREFIX  SUFIX ============================
#printonOK = True
TEST(is_prefix,False, "hola" , "hoja"  )
TEST(is_prefix,False, "hola" , "hoja"  )
TEST(is_prefix,False, "hoja" , "hola"  )
TEST(is_prefix,False, "ho"   , "hola"  )
TEST(is_prefix,False, "lapiz", "hoja"  )
TEST(is_prefix,False, "hoja" , "lapiz" )
TEST(is_prefix,False, "ho"   , "hola"  )
TEST(is_prefix,True , "hola" , "ho"    )
TEST(is_prefix,True , "hola" , "hola"  )

TEST(is_suffix,False, "cancion", "mansion" )
TEST(is_suffix,False, "mansion", "cancion" )
TEST(is_suffix,False, "sion"   , "cancion" )
TEST(is_suffix,False, "ion"    , "cancion" )
TEST(is_suffix,True , "cancion", "ion"     )
TEST(is_suffix,True , "cancion", "cancion" )

TEST(get_common_prefix, ""   , ""      , ""        )
TEST(get_common_prefix, "asd", "asd"   , "asd"     )
TEST(get_common_prefix, "ca" , "camion", "cancion" )
TEST(get_common_prefix, "g"  , "gato"  , "gusto"   )
TEST(get_common_prefix, ""   , "gato"  , "camion"  )
TEST(get_common_prefix, ""   , ""      , "camion"  )
TEST(get_common_prefix, ""   , "gato"  , ""        )

TEST(get_common_suffix, ""   , ""      , ""        )
TEST(get_common_suffix, "asd", "asd"   , "asd"     )
TEST(get_common_suffix, "ion", "camion", "cancion" )
TEST(get_common_suffix, "to" , "gato"  , "gusto"   )
TEST(get_common_suffix, ""   , "gato"  , "camion"  )
TEST(get_common_suffix, ""   , ""      , "camion"  )
TEST(get_common_suffix, ""   , "gato"  , ""        )
#printonOK = False
#============================== AUTOMATON ==============================
#printonOK = True
def match(text,pattern):
	alp = get_alphabet(text+pattern)
	auto = Automaton(pattern,alp)
	return auto.match(text)

TEST(match,[0,7],"abracadabra","abra")
TEST(match,[2],"abababacaba","ababaca")
TEST(match,[0,6],"do or do not there is no try","do")
#printonOK = False
#============================= SUFFIX TRIE =============================
#printonOK = True

#def makeSuffixTree(string):
#	st = SuffixTree(string)
#	return st.dfs()

#atree = SuffixTree("banana")
#print atree.root.child
#print atree.root.child['a'].child['n'].start, atree.root.child['a'].child['n'].end.end
#print "banana"[atree.root.child['n'].start:atree.root.child['n'].end.end]

#TEST(makeSuffixTree,"a $ 5 na $ 3 na$ 1 banana$ 0 na $ 4 na$ 2","banana")
#TEST(makeSuffixTree,"AT $ 9 CGCGAT$ 3 CG AT $ 7 CGCGAT$ CGAT$ 5 G AT $ 8 CGCGAT$ 2 CGAT$ 6 T $ 10 CG ATCGCGAT$ 0 CGAT$ 4","TCGATCGCGAT")

# TEST(st.search,[5],"CGCG")
# TEST(st.search,[0],"TCGAT")
# TEST(st.search,[1,7],"CGAT")
# TEST(st.search,[1,7],"CGA")
# TEST(st.search,[3,9],"AT")
# TEST(st.search,[1,5,7],"CG")
# TEST(st.search,[0,4,10],"T")

# TEST(st.search,[],"GGCT")
# TEST(st.search,[],"CGATT")
# TEST(st.search,[],"M")
# TEST(st.search,[],"GATO")
# TEST(st.search,[],"ORNITORRINCO")

#printonOK = False
#============================ PATRICIA TRIE ============================
#printonOK = True
pat = Patricia.Node()

def insert(st,i):
	pat.insert(st,st,i)
	r = []
	pat.dfs(r)
	return " ".join(r)

TEST(insert,"roma roma","roma",0)
TEST(insert,"r emo remo oma roma","remo",1)
TEST(insert,"r emo remo om a roma ulus romulus","romulus",2)
TEST(insert,"r em ember remember o remo om a roma ulus romulus","remember",3)
TEST(insert,"r em ember remember o remo om a $ roma ns romans ulus romulus","romans",4)
TEST(insert,"r em ember remember o remo om a $ roma n ce romance s romans ulus romulus","romance",5)
TEST(insert,"r em ember remember o remo om a $ roma n ce romance s romans ulus romulus","roma",6)
TEST(insert,"gato gato r em ember remember o remo om a $ roma n ce romance s romans ulus romulus","gato",7)
TEST(insert,"$ $ gato gato r em ember remember o remo om a $ roma n ce romance s romans ulus romulus","",8)
TEST(insert,"$ $ gato gato r em ember remember o remo om a $ roma n ce romance s romans ulus romulus","remember",9)

def search(st):
	return pat.search(st,st)

TEST(search,[2]  ,"romulus")
TEST(search,[3,9],"remember")
TEST(search,[0,6],"roma")
TEST(search,[8]  ,"")

TEST(search,[],"paralelepipedo")
TEST(search,[],"romanizacion")
TEST(search,[],"rem")
#printonOK = False
print "TEST ENDED"
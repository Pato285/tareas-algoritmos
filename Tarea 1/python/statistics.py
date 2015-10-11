import math

a = open("results.csv",'r')

table = {}
for line in a:
    if line=="ALG\tDATA SET\tPLEN\tIT\tEJECTIME\tNCOM\n": continue;

    row = line[:-1].split('\t')
    #ALG | DATASET | PATLEN | IT | EJECTIME | COMP
    ALG = row[0]
    DATASET = row[1]
    PATLEN = int(row[2])
    IT = int(row[3])
    EJECTIME = float(row[4])
    COMP = int(row[5])

    key = (ALG,DATASET,PATLEN)
    value = (IT,EJECTIME,COMP)
    if table.has_key(key):
        table[key].append(value)
    else:
        table[key] = [value]

#print map(lambda x: len(table[x]),table)
for key in table:
    n = len(table[key][1])
    TIME_avg = sum(table[key][1])/n
    TIME_var = (sum(map(lambda x:x[1]*x[1],table[key]))-n*TIME_avg*TIME_avg)/(n-1)
    #var_estimador = math.sqrt(TIME_var/n)
    print key,TIME_avg,TIME_var

a.close()

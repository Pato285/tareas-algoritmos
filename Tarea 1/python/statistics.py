import math
import sys

if __name__ == '__main__':
    if len(sys.argv)!=3: raise Exception("Uso: statistics.py <input> <output>")
    a = open(sys.argv[1],'r')

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
    a.close()

    a = open(sys.argv[2],'w')
    a.write('ALG\tDATA SET\tPLEN\tAVG T\tSTDEV T\tT ERR\tT CONF INT\tAVG C\tSTDEV C\tC ERR\tC CONF INT\n')

    for key in sorted(table):
        (ALG,DATASET,PATLEN) = key

        (it_list,time_list,comp_list) = zip(*table[key])
        n = len(it_list)

        TIME_avg = sum(time_list)/n
        TIME_stdev = math.sqrt(sum(map(lambda x: (x-TIME_avg)**2,time_list))/n)
        TIME_error = 1.96*TIME_stdev/math.sqrt(n)

        COMP_avg = sum(comp_list)/n
        COMP_stdev = math.sqrt(sum(map(lambda x: (x-COMP_avg)**2,comp_list))/n)
        COMP_error = 1.96*COMP_stdev/math.sqrt(n)

        a.write('%s\t%s\t%s\t%f\t%f\t%f\t[%f to %f]\t%f\t%f\t%f\t[%f to %f]\n' % (ALG,DATASET,PATLEN,TIME_avg,TIME_stdev,TIME_error,TIME_avg-TIME_error,TIME_avg+TIME_error,COMP_avg,COMP_stdev,COMP_error,COMP_avg-COMP_error,COMP_avg+COMP_error))
    a.close()

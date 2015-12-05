# Write a binary file with several C strings.
# 32 bit integer with a magic number.
# 32 bit integer with the number of elements (indexes).
# 32 bit integer with the number of bytes for all the strings.
# 32 bit integer: Offset were the indexes start
# 32 bit integer: Offset were the strings start
# 32 bit integers indexes
# bytes: all the strings, each string end with \0

import re
import struct
import sys

REGEX = re.compile("[^a-zA-Z ]")

if __name__ == '__main__':
    if len(sys.argv)!=3: raise Exception("Requires in txt filename and potato out filename.")
    txtin = open(sys.argv[1],'r')
    buff= ""
    for line in txtin:
        buff += line
    txtin.close()
    buff = REGEX.sub('',buff)
    buff = buff.lower()
    buff = buff.split()
    # Potato file *.pto
    binout = open(sys.argv[2], 'wb')
    elem_num = len(buff)
    byte_num = sum(map(lambda x:len(x)+1,buff)) #TODO: check this
    off_idx = 5*4
    off_str = elem_num*4 + off_idx
    binout.write(struct.pack('i',1214793300))#magic number
    binout.write(struct.pack('i',elem_num))
    binout.write(struct.pack('i',byte_num))
    binout.write(struct.pack('i',off_idx))
    binout.write(struct.pack('i',off_str))
    idx = 0
    for b in buff:
        binout.write(struct.pack('i',idx))
        idx += len(b)+1
    for b in buff:
        binout.write(b)
        binout.write(chr(0))
    binout.close()

import sys
import colorsys
import csv

argvs = sys.argv
argc = len(argvs)

src = "colors.csv" if argc <= 1 else argvs[1]
dest = "colors.h" if argc <= 2 else argvs[2]

fp = open(src, 'r')
wfp = open(dest, 'w')

reader = csv.reader(fp)

def toHsv(rgbstr):
    rgbstr = rgbstr.strip()
    c = tuple(int(rgbstr[i:i+2], 16) for i in (1, 3, 5))
    c = colorsys.rgb_to_hsv(c[0] / 255, c[1] / 255, c[2] / 255)
    return "{:d},{:d},{:d}".format(int(c[0] * 255), int(c[1] * 255), int(c[2] * 255))

for row in reader:
    wfp.write("#define {} {}\n".format(row[0], toHsv(row[1])))

fp.close()
wfp.close()

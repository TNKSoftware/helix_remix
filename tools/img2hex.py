from PIL import Image
import numpy
import sys

argvs = sys.argv
argc = len(argvs)

src = "src.png" if argc <= 1 else argvs[1]
dest = "res.txt" if argc <= 2 else argvs[2]

print("{} => {}".format(src, dest))

img = Image.open(src).convert('RGB')
data = numpy.array(img)

w,h = img.size

sw = w
if sw % 8 != 0:
	sw = sw + (8 - (sw % 8))

print("(Width, Height, Stride) => ({},{},{})".format(w, h, sw))

v = 0x00
pos = 0
ot = 0

f = open(dest, "w")

for y in range(h):
	for x in range(sw):
		if x >= w:
			c = 0
		else:
			c = 1 if data[y,x][0] < 128 else 0

		v = v | (c << pos)
		pos = pos + 1
		if pos >= 8:
			f.write("0x{:02X},".format(v))
			v = 0x00
			pos = 0
			ot = ot + 1
			if ot == 20:
				f.write("\n")
				ot = 0

f.close()

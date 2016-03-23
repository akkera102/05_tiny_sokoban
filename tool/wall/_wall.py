# -*- coding: utf-8 -*-

import Image
import ImageDraw


im = Image.open("base.bmp")
dw = ImageDraw.Draw(im)
cx = im.size[0]
cy = im.size[1]
b  = 0

for y in range(0, cy, 8):
	for x in range(0, cx, 8):
		if not (b & 0x01): dw.point((x, y), 255)
		if not (b & 0x02):  dw.line((x + 1, y, x + 6, y), 255)
		if not (b & 0x04): dw.point((x + 7, y), 255)

		if not (b & 0x08):  dw.line((x, y + 1, x, y + 6), 255)
		if not (b & 0x10):  dw.line((x + 7, y + 1, x + 7, y + 6), 255)

		if not (b & 0x20): dw.point((x, y + 7), 255)
		if not (b & 0x40):  dw.line((x + 1, y + 7, x + 6, y + 7), 255)
		if not (b & 0x80): dw.point((x + 7, y + 7), 255)
		b += 1

im.save("wall.bmp")

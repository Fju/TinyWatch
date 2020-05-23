from PIL import Image, ImageDraw, ImageFont
import numpy as np
import matplotlib.pyplot as plt

import argparse

parser = argparse.ArgumentParser(description="Generate byte arrays of font characters.")
parser.add_argument("--width", type=int, help="character width")
parser.add_argument("--height", type=int, help="character height")

parser.add_argument("--offset-x", type=int, help="")
parser.add_argument("--ofset-y", type=int, help="")
parser.add_argument("--size", type=int, help="font size")
parser.add_argument("chars", type=str, metavar="CHARS", nargs=1, help="characters to process")

args = parser.parse_args()

def draw_character(char):
    pil_font = ImageFont.truetype("monaco.ttf", size=args.size, encoding="unic")

    canvas = Image.new("1", [args.width, args.height])

    draw = ImageDraw.Draw(canvas)
    draw.text((0, -int(args.size / 5)), char, font=pil_font, spacing=0, fill="#ffffff")

    return np.asarray(canvas)

def array_to_hex(arr):
    num = 0
    for i in range(8):
        num = num | (arr[i] << (7 - i))
    h = hex(num)

    if len(h) == 3:
        h = "0x0" + h[-1]

    return h


result = ""

print(args.chars)
for c in args.chars[0]:
    result += "// %s\n" % c
    mat = draw_character(c)

    for y in range(mat.shape[0]):
        for x in range(mat.shape[1] // 8):
            result += array_to_hex(mat[y, x*8:(x+1)*8]) + ", "

        result += " // %s\n" % ("".join([ str(j*1) for j in mat[y] ]))
 
    # save image as preview
    plt.imshow(mat)
    plt.savefig("preview_%s.png" % c)

print(result)

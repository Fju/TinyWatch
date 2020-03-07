from PIL import Image, ImageDraw, ImageFont
import numpy as np
import matplotlib.pyplot as plt


CHAR_WIDTH = 24
CHAR_HEIGHT = 35

def draw_character(char):
    pil_font = ImageFont.truetype("monaco.ttf", size=45, encoding="unic")

    canvas = Image.new("1", [CHAR_WIDTH, CHAR_HEIGHT])

    draw = ImageDraw.Draw(canvas)
    draw.text((-1, -10), char, font=pil_font, fill="#ffffff")

    return np.asarray(canvas)

def array_to_hex(arr):
    num = 0
    for i in range(8):
        num = num | (arr[i] << (7 - i))
    h = hex(num)

    if len(h) == 3:
        h = "0x0" + h[-1]

    return h


result = "";
for i in range(10):
    result += "// %d\n" % i
    mat = draw_character(str(i))

    for y in range(CHAR_HEIGHT):
        for x in range(CHAR_WIDTH // 8):
            result += array_to_hex(mat[y, x*8:(x+1)*8]) + ", "

        result += " // %s\n" % ("".join([ str(j*1) for j in mat[y] ]))
 
    # save image as preview
    plt.imshow(mat)
    plt.savefig("test_%d.png" % i)

print(result)

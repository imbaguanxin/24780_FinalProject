from PIL import Image
import os

def flip_horizontal(picname):
    with Image.open(picname) as im:
        im = im.transpose(Image.FLIP_TOP_BOTTOM)
    name, suffix = os.path.splitext(picname)
    newpath = name + '_fliph' + suffix
    im.save(newpath) 

flip_horizontal('banana_air.png')
flip_horizontal('banana_l.png')
flip_horizontal('banana_r.png')
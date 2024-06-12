#!/usr/bin/env python3
from PIL import Image
from PIL import ImageDraw

# 读取一张图片
image = Image.open("/home/lxn/leetcode/script/1.jpg")
# 显示图片
image.show()
image_draw = ImageDraw.Draw(image)
# 画一条线
image_draw.line((10, 10, 100, 100), fill=(0, 255, 0), width=10)
# 绘制矩形
x1,y1,x2,y2 = 100,200,300,400
color_list = ["red", "green", "blue", "yellow", "black", "white"]
image_draw.rectangle(xy=(x1,y1,x2,y2), fill="red", width=5)
# 将绘制过的图片保存
image.save("/home/lxn/leetcode/script/output.jpg")
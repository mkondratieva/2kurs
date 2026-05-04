from scipy import misc  #пример использования метода обратных растояний
import numpy as np
import copy

import math
#from imageio import imread, imwrite

def black_sq(im,a,b):# вырезаем на изображении квадратную дырку   40 на 40
	for y in range (a-20, a+20):
		for x in range (b-20, b+20):
			im[y][x]=0,0,0

def obr_rasst(im): #реализация интерполяции
	for y in range (a-20, a+20):
		for x in range (b-20, b+20):#обход пикселей внутри дырки
			for q in range(3):
				H=0.
				S=0.
				for y1 in range (a-30, a+30, 2): #в качестве узлов берем рамку вокруг дырки размера 60 на 60
					for x1 in range (b-21, b-30, -2):
						hi=math.sqrt((x-x1)**2 + (y-y1)**2)
						hi=(1./hi)**p
						S+=im[y1][x1][q]*hi
						H+=hi
    
				for y1 in range (a-30, a+30, 2): #обход узлов справа от дырки
					for x1 in range (b+21, b+30, 2):
						hi=math.sqrt((x-x1)**2 + (y-y1)**2)
						hi=(1./hi)**p
						S+=im[y1][x1][q]*hi
						H+=hi
				for y1 in range (a-21, a-30, -2): #обход узлов снизу от дырки
					for x1 in range (b-21, b+21, 2):
						hi=math.sqrt((x-x1)**2 + (y-y1)**2)
						hi=(1./hi)**p
						S+=im[y1][x1][q]*hi
						H+=hi
				for y1 in range (a+21, a+30, 2):
					for x1 in range (b-21, b+21, 2): #обход узлов сверху от дырки
						hi=math.sqrt((x-x1)**2 + (y-y1)**2)
						hi=(1./hi)**p
						S+=im[y1][x1][q]*hi
						H+=hi
				im[y][x][q]=S/H   #подставляем в формулу интерполяции, р выбрали случайно

im0=misc.face()
print(im0.shape)

misc.imsave('res0.bmp', im0) #исходное изображение

im=copy.copy(im0)

h= len(im)
w=len(im[0])

a=h//2-60
b=w//2+90

black_sq(im,a,b)

misc.imsave('res1.bmp', im)  # вывод изображения, которе будем обрабатывать

p=11

obr_rasst(im)

misc.imsave('res2.bmp', im) #вывод результата
  

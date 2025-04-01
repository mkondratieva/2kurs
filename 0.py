# транспонировать матрицу изображения
from imageio.v2 import imread, imwrite  # для Win

from scipy import misc
import numpy as np
import os

face=misc.face() # работаем с библиотечным изображением
imwrite('face.bmp', face) # для Win
#misc.imsave('face.bmp', face,format='bmp') #Linux: записали в файл (ради примера, а не ради задачи)
im= imread('face.bmp') # для Win  
#im= misc.imread('face.bmp') #Linux: открыли входной bmp-файл (его можно создать в программах Paint (Win), KolorPaint (Linux)) 

h=len(im) # количество точек изображения по вертикали
w=len(im[0]) # количество точек по горизонтали
print('width=',w,'height=',h)
im1 = np.empty (( w , h , 3 ), dtype = np.uint8) #строим 3-мерный массив, в которой запишем цвета точек выходного изображения (размеры его w по вертикали, h по горизонтали)

for ix in range(w): #перебираем индексы столбцов исходного изображения 
  for iy in range(h):#перебираем точки столбца исходного изображения
     im1[ix][iy]=im[iy][ix] #записываем цвет точки исходного изображения в найденную позицию  транспонированной матрицы, копируются 3 RGB-компоненты цвета, столбец исходной матрицы будет строкой выходной

for ix in range(w):  #нарисуем красную диагональ
  for iy in range(h):
     if(ix==iy):# если точка лежит на главной диагонали
        im1[ix][iy]=(255,0,0)  # перекрашиваем точку в красный

imwrite('face+.bmp', im1) # для Win
#misc.imsave ('face+.bmp', im1,format='bmp')


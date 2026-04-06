# транспонировать матрицу изображения
#from imageio.v2 import imread, imwrite  # для Win

from scipy import misc
import numpy as np
import os

face=misc.face() #работаем с библиотечным изображением
#imwrite('face.bmp', face) # для Win
misc.imsave('face.bmp', face,format='bmp') #записали в файл (ради примера, а не ради задачи)

#im= imread('face.bmp') # для Win  
im= misc.imread('face.bmp') #открыли входной bmp-файл (его можно создать в программах Paint (Win), Kolor Paint (Linux)) и сохраняем рисунок как 24-разрядный bmp-файл

h=len(im) # количество точек изображения по вертикали
w=len(im[0]) # количество точек по горизонтали
print('width=',w,'height=',h)#размер входного изображения w*h
im1 = np.empty (( w , h , 3 ), dtype = np.uint8) #строим 3-мерный массив, в которой запишем цвета точек выходного изображения, размер выходного изображения h*w

for ix in range(w): # перебираем строки исходного изображения = столбцы выходного
  for iy in range(h):#перебираем точки строки
     im1[ix][iy]=im[iy][ix] #записываем цвет точки исходного изображения в найденную позицию  транспонированной матрицы, копируются 3 RGB-компоненты цвета
for ix in range(h):  #нарисуем красную диагональ
  for iy in range(w):
     if(ix==iy):# если точка лежит на главной диагонали
        im1[iy][ix]=(255,0,0)  # перекрашиваем точку в красный

#imwrite('face+.bmp', im1) # для Win
misc.imsave ('face+.bmp', im1,format='bmp')

im2 = np.empty (( h , w , 3 ), dtype = np.uint8) #строим 3-мерный массив, в которой запишем цвета точек дважды транспонированного изображения

for ix in range(h): # перебираем строки  изображения im1= столбцы im2
  for iy in range(w):#перебираем точки строки
     im2[ix][iy]=im1[iy][ix] #записываем цвет точки исходного изображения в найденную позицию  транспонированной матрицы, копируются 3 RGB-компоненты цвета

#imwrite('face++.bmp', im2) # для Win
misc.imsave ('face++.bmp', im2,format='bmp')


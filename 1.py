# транспонировать матрицу изображения
#from imageio.v2 import imread, imwrite  # для Win

from scipy import misc
import numpy as np
import os
a=np.empty(3, dtype = np.uint8)
a[0]=0; a[1]=60;a[2]=0;
print(not a.any(),a.all());

def draw(a,b):
    if a==b:
        return
    if(abs(a[0]-b[0])>abs(a[1]-b[1])):   # y=a[1]+k(x-a[0])
           if a>b:
               a,b=b,a
           k=(a[1]-b[1])/(a[0]-b[0]); 
           for x in range(a[0],b[0]):
                y=a[1]+int(k*(x-a[0]))
                if x>=w or y>=h:
                    continue
                im[y][x]=255,0,0
            
im= misc.imread('1.bmp') #Linux: открыли входной bmp-файл (его можно создать в программах Paint (Win), KolorPaint (Linux)) 
#im= imread('1.bmp') #Linux: открыли входной bmp-файл (его можно создать в программах Paint (Win), KolorPaint (Linux)) 

h=len(im) # количество точек изображения по вертикали
w=len(im[0]) # количество точек по горизонтали
print('width=',w,'height=',h)

for i in range(w):
    im[0][i]=255,0,0

draw((0,0),(w,h))  #главная диагональ изображения
draw((w,0),(0,h)) #побочная диагональ

misc.imsave ('face+.bmp', im,format='bmp')
#imwrite('face+.bmp', im,format='bmp')

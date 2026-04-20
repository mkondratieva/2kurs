"""
Формат вызова программы должен быть следующим: 
python3 prog InputFile OutputFile 
"""
import sys
import numpy as np  
import random                               

#Программа должна загрузить изображение из  графического файла  InputFile 

if len(sys.argv)>2:
	im= misc.imread(sys.argv[1])
else:
	print("err");
	exit(0)
h=len(im)                                          
w=len(im[0])
print('width=',w,'height=',h)
def draw(a,b): #дописать, проверить и изменить под условие 
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
                if im[y][x].any():
	                im[y][x]=255,0,0
    else:
            print("???")

    im[a[1]][a[0]]=(255,0,0)
    im[b[1]][b[0]]=(255,0,0)

list=[] #создать список черных точек изображения
"""
....

"""
A=(0,h//2)  #пусть А -- некоторая точка изображения
def task(): 
	while True: #Следующую процедуру надо выполнять, пока изменяется изображение:
		flag=0
		#......
		#while...
			#if random.random()<0.3:
				#flag=1......
		if flag==0:
			break;
"""
Для всех черных пикселей (перебирать их надо с помощью созданного
списка) с вероятностью 0.3  следует соединить их с А 
отрезком красного цвета любым  алгоритмом....
"""

task()
#Полученное изображение следует вывести в графический файл  OutputFile 
	
misc.imsave(sys.argv[2], im, format='bmp')


 
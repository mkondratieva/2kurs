from tkinter import *  #рисует точки со случайными координатами, после нажатия клавиши стрелка направо соединяет их
import math
from random import randint,random

max_X=1200 #ширина окна (количество точек по горизонтали)
max_Y=800  # высота окна
e_x= 6.0  #количество единичных отрезков по полож. части оси х в преобразованной системе координат
e_y= e_x*max_Y/max_X#кол-во единичных отр. по полож. части оси у из условия их рав-вва по длине 

n=4  #количество точек

class Point:# точка плоскости с целыми координатами (в исходной системе координат)
    def __init__(self, a,b):#конструктор класса
        self.x=a
        self.y=b
    def draw_line(self,other,color='black'):#рисование линии на холсте, цвет по умолчанию - черный
        c.create_line(self.x, self.y, other.x, other.y,width=3,fill=color)
    def draw_triagle(self,other1,other2,color='black'):#заливка треугольника
        c.create_polygon(self.x, self.y, other1.x, other1.y,other2.x, other2.y,fill=color)
    def draw_circle(self,radius=0.03,color='black'):#рисование окружности на холсте
        r=RPoint(radius,radius)# овал вписан в прямоугольник, выч. его границ
        c.create_oval((self-r).x, (self-r).y,(self+r).x,(self+r).y,fill=color)#исп. -

class RPoint(Point):#дочерний класс  точка с вещест. координатами для реальной работы

    def __init__(self, a,b):
        self.x_=a
        self.y_=b
        self.x=max_X*(a/e_x+1.)/2.#пересчет координат из системы координат в центре окнав и единичными отрезками e_x, e_y в исходную (с центром влевом верхнем углу)
        self.y=max_Y*(-b/e_y+1.)/2.
    def __add__(self,other):#сложение точек (векторов)
        return RPoint(self.x_+other.x_,self.y_+other.y_)
    def __sub__(self,other):# разность точек(векторов)
        return RPoint(self.x_-other.x_,self.y_-other.y_)
    def __mul__(self,other):#векторное произведение
        return self.x_*other.y_-self.y_*other.x_

def draw(p): #рисуем точки из списка
    for u in p:
        u.draw_circle()

root = Tk()
c = Canvas(width=max_X, height=max_Y, bg='white')#приготовление холста для рисунка
c.focus_set()
c.pack()

c.create_text(300,70, text="Нажмите на клавиатуре стрелку вправо", fill="black", font=("Helvectica", "25"))


RPoint(-e_x,0.).draw_line(RPoint(e_x,0.))#горизонтальная ось
RPoint(0.,e_y).draw_line(RPoint(0.,-e_y))#вертикальная ось

RPoint(-0.1,1.).draw_line(RPoint(0.1,1.))#горизонтальная метка -единичный отрезок
RPoint(1.,0.1).draw_line(RPoint(1.,-0.1))#вертикальная

polygon=[]#список точек

for u in range(n): # заполняем список точками со случайными координатами
     polygon.append((RPoint(randint(-e_x,e_x),randint(-e_y,e_y))))

draw(polygon)

def draw_path(event):#обработчик события
    a=0
    for u in polygon: #для каждой точки списка
        if a>0:
            u.draw_line(v,'red') #соединяем красной линией 2 соседние точки
        a+=1 
        v=u
    polygon[0].draw_line(polygon[-1],'red') #первую точку соединяем с последней


c.bind('<Right>',  draw_path)# к клавише стрелочка направо привязываем действие

root.mainloop()#бесконечный цикл

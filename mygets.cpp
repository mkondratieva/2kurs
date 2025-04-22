#include <iostream>
#include <stdio.h> 
#include <stdlib.h>
#include<time.h>
#include<cstring>
using namespace std;

char *mygets(char *&str, size_t &LMax, FILE *in){ //на длину строки нет ограничений
        int begin=0; //это номер позиции в строке для загрузки очередного блока символов
        if(!str)
                str=new char[LMax];//(char *)malloc(*LMax); //считываем блоками размера *LMax
        while(fgets(str+begin,LMax-begin,in)){//туда, где закончилась  строка, полученная на предыдущей итерации, кладем следующий извлеченный из файла блок символов
                begin=LMax-1; //передвигаемся туда, где должен быть конец строки
                if(strchr(str,'\n')) //если строка считалась до конца
                        break; //заканчиваем с текущей строкой
                LMax*=2;  //иначе размер блока удваиваем
                char *buf=new char[LMax];
                strcpy(buf, str);
                delete [] str;
		str=buf;
        }
        if(begin==0){ //сюда попадаем, только если достигнут конец файла
                delete [] str;
                return nullptr;
        }
        return str;
}

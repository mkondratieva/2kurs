#include <iostream>
#include <ctime>
using namespace std;
struct Base;
struct Factory_Base{ //иерархия клсса фабрика должна повторять иерархию класса, который она обслуживает
	 virtual Base * create()=0;//основная фабрика ничего не производит, т.к. Base будет абстрактным
};
struct Base{
	void pr(){ 
		foo();
	}
        virtual void g()=0; //чисто виртуальная функция, которая делает класс абстрактным
	virtual void foo(){ 
		puts("Base");
	}
	virtual  ~Base(){ 
	}
	static Base * create(int i, Factory_Base **f){//базовый класс не должен знать о наследниках, но допускает наличие фабрик для их генерации
	        return f[i]->create();
	}
};
struct Child:Base{   
	void foo()override { 
		puts("Child"); 
	}
	void g(){} //В ДОЧЕРНМ КЛАССЕ ЧИСТО ВИРТУАЛЬНАЯ ФУНКЦИЯ ОБЯЗАНА БЫТЬ ПЕРЕГРУЖЕНА
	Child(const Base&){}
	Child(){}  
};
struct Factory_Child:Factory_Base{
        virtual Base *create(){return new Child();}
};
struct Child1:Base{   
	void foo()override { 
		puts("Child1"); 
	}
	void g(){}
	Child1(const Base&){}
	Child1(){}  
};
struct Factory_Child1:Factory_Base{
        virtual Base * create(){return new Child1();}
};
Child operator+(const Base &b, const Base &){//+ должен возвращать объект, но, т.к. объектов базоваго класса не существует,  выбираем один из дочерних
        return b;
} 
int main(){ 
	Factory_Base *f[]={new Factory_Child1, new Factory_Child};//создаем массив указателей на фабрики
	Base *mass[5];//массив указателей на базовый класс. В реальности некоторые указатели будут указывать на объекты дочернего класса
	srand(time(0));
 	for(size_t i=0;i<5;i++)
              mass[i]=Base::create(rand()%2,f);
	puts("_______");
	for(size_t i=0;i<5;i++)
	     mass[i]->pr();
	puts("_______");
   	Child1 sum;
    	for(size_t i=0;i<5;i++)
	    sum=sum+*mass[i];
        sum.pr();
	puts("");
	for(size_t i=0;i<5;i++)
	     delete mass[i];
	delete f[0];delete f[1];	
	return 0;
}

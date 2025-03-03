#include <iostream>
#include <fstream>
#include <ctime>
#include<sstream>
#include<vector>
using namespace std;
struct Base;
struct Factory_Base{ //иерархия клсса фабрика должна повторять иерархию класса, который она обслуживает
	 virtual Base * create(const string&)=0;//основная фабрика ничего не производит, т.к. Base будет абстрактным
};
struct Base:string{ //Base дочерний класс скласса string
	Base(const string &s):string(s){}
	void pr(){ 
		foo();
	}
        virtual void g()=0; //чисто виртуальная функция, которая делает класс абстрактным
	virtual void foo(){ 
		puts("Base");
	}
	virtual  ~Base(){ 
	}
	static Base * create(const string&s, vector<Factory_Base *>&f){ //с помощьюмасива абрик  по строке файла создает укаатель на Base
		int type=-1;
		stringstream in(s); //из строки создаем поток
		in>>type;
		if(type!=0&&type!=1)throw string("Bad type");//извлекам из этого потока число (тип дочернего кдасса(
		string buf;
		if(!(in>>buf))throw string("Bad namr"); //извлекаем имя файла и в случае ошибки выбрсываем исключение
		if(in>>buf)throw "trush"+buf;//проверяем наличие мусора в строке
		return f[type]->create(buf);//по номеру фабрики возвращаем указатель на созданный  объект
	}
};
struct Child:Base{   
	void foo()override { 
		ofstream out(*this,ios::app); //в файл с именем, которое хранится в строке, выводим тип дочернего класса
  		out<<*this<<"  Child\n";
	}
	void g(){} 
	Child(const Base&s):Base(s){}
	Child(const string &s):Base(s){} 

};
struct Factory_Child:Factory_Base{
        virtual Base *create(const string&s){return new Child(s);}
};
struct Child1:Base{   
	void foo()override{ 
		ofstream out(*this,ios::app);
  		out<<*this<<"  Child1\n";
	}
	void g(){}
	Child1(const Base&b):Base(b){}
	Child1(const string &s):Base(s){}  
};
struct Factory_Child1:Factory_Base{
        virtual Base * create(const string&s){return new Child1(s);}
};
Child operator+(const  Base &b, const Base &b1){//+ должен возвращать объект, но, т.к. объектов базоваго класса не существует,  выбираем один из дочерних
	Child tmp(b);
	tmp+=b1; //+= дописывает в конец одой строки другую. Определен в string, поэтому работает для дочерних классов
	return tmp;// подклеивает к строке первого слагаемого строку второго
} 
int main(){ 
	vector<Factory_Base *>f={new Factory_Child, new Factory_Child1};//создаем массив указателей на фабрики
	vector<	Base *>mass;//массив указателей на базовый класс. В реальности некоторые указатели будут указывать на объекты дочернего класса
	string s;    
	ifstream in("input.txt");
	try{  	
		for(;getline(in,s);){//пытаемся прочитать строку из входноо файла
                      mass.push_back(Base::create(s,f));//по этой строке создаем с помощью массива фабрик указатель на  Base
		}
	}
	catch(const string &f){
		cout<<"err "<<f;//ловим исключения 
	}
	puts("_______");
	for(auto t:mass)
		t->pr();
	puts("_______");
	auto it=mass.begin();

	if(!mass.empty() ){//если полученный массив не пуст
	   	Child1 tmp(**it);//циклический сдвиг
		for(;it!=mass.end()-1;++it)
			**it=**(it+1);
  		**it=tmp;//it указывает на последний элемент nass
		for(auto t:mass)
			t->pr();
		puts("_______");
		--it;   //просуммируем остальные элементы (кроме последнего, который лежит в tmp
		for(;it!=mass.begin()-1;--it)
	    	tmp=**it+tmp;
        	tmp.pr();
	}
	puts("");
	for(auto t:mass)
		delete t;	
	for(auto t:f)	
		delete t;;	
	return 0;
}

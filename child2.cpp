#include <iostream>
#include <ctime>
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
	static Base * create(const string&s, vector<Factory_Base *>&f){//базовый класс не должен знать о наследниках, но допускает наличие фабрик для их генерации
		return f[rand()%2]->create(s);
	}
};
struct Child:Base{   
	void foo()override { 
  		cout<<*this<<"Child\n";
	}
	void g(){} //В ДОЧЕРНМ КЛАССЕ ЧИСТО ВИРТУАЛЬНАЯ ФУНКЦИЯ ОБЯЗАНА БЫТЬ ПЕРЕГРУЖЕНА
	Child(const Base&s):Base(s){}
	Child(const string &s):Base(s){} 

};
struct Factory_Child:Factory_Base{
        virtual Base *create(const string&s){return new Child(s);}
};
struct Child1:Base{   
	void foo()override{ 
  		cout<<*this<<"Child1\n";
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
	vector<Factory_Base *>f={new Factory_Child1, new Factory_Child};//создаем массив указателей на фабрики
	vector<	Base *>mass={0,0,0,0,0};//массив указателей на базовый класс. В реальности некоторые указатели будут указывать на объекты дочернего класса
	srand(time(0));
	string s;
	for(auto &t:mass) {
		cin>>s;
              t=Base::create(s,f);
	}
	puts("_______");
	for(auto t:mass)
		t->pr();
	puts("_______");
   	Child1 sum("{{{{{{");
	for(auto t:mass)
	    sum=sum+*t;
        sum.pr();

	puts("");
	for(auto t:mass)
		delete t;	

	for(auto t:f)	
		delete t;;	
	return 0;
}

#include <iostream>
#include <fstream>
#include <ctime>
#include<sstream>
#include<vector>
#include<chrono>
#include<omp.h>
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
Child operator+(const  Base &b, const Base &b1){
    return Child("++++");//+ должен возвращать объект, но, т.к. объектов базоваго класса не существует,  выбираем один из дочерних
	Child tmp(b);
	tmp+=b1; //+= дописывает в конец одой строки другую. Определен в string, поэтому работает для дочерних классов
	return tmp;// подклеивает к строке первого слагаемого строку второго
} 
int main(){ 
    //omp_set_num_threads (1);   //можно указать количество потоков
        int N=111111;
	vector<Factory_Base *>f={new Factory_Child, new Factory_Child1};//создаем массив указателей на фабрики
	vector<	Base *>mass(N);//dtrnjh указателей на базовый класс. В реальности некоторые указатели будут указывать на объекты дочернего класса
	string s;    
        vector <string> str;//вспомогательный вектор строк файла
	ifstream in("input.txt");
	try{  	
		for(;getline(in,s);){//пытаемся прочитать строку из входноо файла
		   str.push_back(s);//запоминаем все строки в str
        	}
		size_t  n=str.size();
    		auto start = std::chrono::system_clock::now();
		#pragma omp parallel for//распараллеливание цикла for
    		for(size_t i=0;i<N;i++)
        		mass[i]=Base::create(str[i%n],f);
    		if(!mass.empty()){//если полученный вектор не пуст
			auto it=mass.begin();
		        Child1 tmp(*mass[0]);
			#pragma omp parallel for //т.к. итерации для такого сложения независимы, можно распараллелить так
        		for(auto it=mass.begin();it!=mass.end();++it)
				tmp=**it+tmp;
	        	tmp.pr();
    		}
 	        auto end = std::chrono::system_clock::now();    
	        int elapsed_ms = static_cast<int>(chrono::duration_cast<std::chrono::milliseconds>(end - start).count());			
	        cout <<"time is " <<elapsed_ms <<" ms\n";
		for(auto t:mass)
		delete t;	
		for(auto t:f)	
		delete t;
		auto it=mass.begin();
	}
	catch(const string &f){
		cout<<"err "<<f;//ловим исключения 
	}
	return 0;        
}

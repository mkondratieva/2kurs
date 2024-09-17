#include<iostream>
using namespace std;

class A{  
	int *u=nullptr; //массив, для которого будем выделять место в куче
	public: 
	A(){  //конструктор без параметров
		u=new int[11];
	} 
	~A(){ //деструктор, вызывается неявно
		puts("destr"); delete[]u;
	}
	A(const A&other){ 
		puts("copy");//конструктор копии, не нужен для простого класса 
		u=new int[11];
		u[0]=other.u[0];
	}
	A(A&&other){ 
		puts("copy&&");//конструктор копиирования перемещением
		u=other.u;
	        other.u=nullptr;
	}
	A& operator=(const A&other){
        	if(this==&other)
            		return *this;
        	delete []u;
		u=new int[11];
		u[0]=other.u[0];
	        return *this;
	}
	A operator +(int){
		A tmp;
		tmp.u[0]=11;
		return tmp;
	}
	friend ostream &operator <<(ostream &stream, const A &obj){
		stream<<obj.u[0];
		return stream;
	}
	//int func(){????}
	//int func(){????}
	
};
int  func(const A &){ //функция может работать как для lvalue, так и для rvalue-объектов
        return 0;
}
int  func(A &&){//только для rvalue-объектов
        return 1;
}
int main(){ 
    int x; x=1; int &y=x;//y - обычная ссылка (lvalue)
    y=0; cout<<x<<" "<<y<<"\n";
    int &&z=1;// z - ссылка на литерал (криорый, наряду с временным и анонимным объектами является rvalue)
    z=0;
    cout<<z;
    A w;
    cout<<"\nfunc="<<func(w+1)<<func(w)<<"\n"; //вывод  10
//нужно понимать, почему именно так
    return 0;
}
	

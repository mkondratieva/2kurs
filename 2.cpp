#include<iostream>
#include<memory>
using namespace std;
struct S{int *p=nullptr;    //модель unique_ptr
	S(){p=new int;}
	~S(){delete p;}
	S(const S&)=delete;
	S( S&&o){
		p=o.p;o.p=nullptr;}

};
class A{  
	//S u;
public:	shared_ptr<int[]> u=shared_ptr<int[]>(new int[1]);
	public: 
	A operator +(const int a){
		A tmp;
		tmp.u[0]=11; // tmp.u.p[0]=11;
		return tmp;
	}
	A copy(){A tmp; tmp.u[0]=u[0];return tmp;}
	friend ostream &operator <<(ostream &stream, const A &obj){
		stream<<obj.u[0];
	//	stream<<obj.u.p[0];
		return stream;
	}
	
};
int main(){ 
	//int *p=new int;
	unique_ptr<int> p=unique_ptr<int>(new int),u(move(p));//u(p) нельзя копировать, но можно перемещать
	*u.get()=0;
	cout<<*u.get()<<"\n"; // но *p.get() нельзя
	A q,x(q) ;//x(q) нельзя, ели  А реализован через S
	x=q=q+1;
	cout<<x<<" "<<q<<"\n"; //11 11
//	cout<<q+1<<"\n"; //11 

	x=x.copy();//нужно понимать, для чего метод copy
	x.u[0]=9;
	cout<<x<<" "<<q<<"\n"; //11 9
	//delete p; //иначе будет утечка
	return 0;
}
	

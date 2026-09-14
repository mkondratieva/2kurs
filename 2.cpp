 #include<iostream>
using namespace std;

class A{  
	int *k;
	public:
	A(){  
		k=new int(7);//конструктор без параметров
	} 
	A operator +(const A&o)const{ 
		A tmp(*this);
		*tmp.k+=*o.k;
		return tmp;
	}

	friend ostream &operator <<(ostream &stream, const A &o){//оператор вывода в поток  объекта класса А
		stream<<*o.k<<"\n";
		return stream;
	}
};
int main(){ 
	A x; cout<<x;x+x; cout<<x<<"\n";
	return 0;
}
	

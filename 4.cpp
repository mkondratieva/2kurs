 #include<iostream>
using namespace std;

class A{  
	int *k;
	public:
	A(){  
		k=new int(7);//конструктор без параметров
	} 
	A(const A&o){  
		puts("copy");//конструктор копии копированием
		k=new int(*o.k);
	}

	A( A&&o){  
		puts("copy&&"); //конструктор копии перемещением , НЕ ТРЕБУЕТ ОТВЕДЕНИЯ ПАМЯТИ
		k=o.k;//отбираем ресурс у  r-value объекта о
		o.k=nullptr;//чтобы после смерти о  его ресурс не пропал
	}

	~A(){
		puts("destr");
		delete k;
	}
	A operator +(const A&o)const{ 
		A tmp(*this);
		*tmp.k+=*o.k;
		return tmp;
	}

	A method()const &{
		cout<<"A&"<<*this<<"\n";
		return *this;
	}
	A &&method()&&{
		cout<<"A&&"<<*this<<"\n";
		return (A&&)(*this);
	}
	friend ostream &operator <<(ostream &stream, const A &o){//оператор вывода в поток  объекта класса А
		stream<<*o.k<<"\n";
		return stream;
	}
	A&operator++(){(*k)++;return *this;}
	A operator++(int){A tmp(*this);(*k)++;return tmp;}
};
void funct(int &&x){x++;cout<<"&&"<<x<<"\n";}
void funct(const int &x){cout<<"&"<<x<<"\n";}
int main(){ 
	//const int&//	
	int &&  y=1; //rvalue ссылка (т.к. 1 -- литерал)
	cout<<y+1<<"\n";
	y+=8; //только для &&
	cout<<y<<"\n";

	int z=11; 
	funct(z);//будет вызван &-вариант fucct
	funct(88); //будет вызван &&-вариант fucct

	funct(y);//будет вызван &-вариант fucct! (т.к. ссылка на rvalue-объект не является rvalue-объектом!
	funct((int &&)y);//будет вызван &&-вариант fucct
	puts("________________________");


	{A x;(++x).method().method().method(); }
	puts("________________________");

	A p=A(); //явный вызов конструктора копии перемещением
	cout<<p<<"\n";
	return 0;
}
	

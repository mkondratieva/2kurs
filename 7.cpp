 #include<iostream>
using namespace std;

class A{  
	int t[2]; 
	class B{
		int *data; size_t i;
		public:
		B(int *a,size_t b):data(a),i(b){}

		void operator=(int k){
			if(k==1)data[i/32]|=1<<i%32;
			else  data[i/32]&=~(1<<i%32);
		}
	};
	public:
	B operator[](size_t i){ //+ВЫБРОСИТЬ ИСКЛЮЧЕНИЕ
		return  B(t,i);
	}
	int operator[](const size_t i)const{  //+ВЫБРОСИТЬ ИСКЛЮЧЕНИЕ
		return  t[i/32]>>(i%32) &1;
	}
	friend ostream &operator <<(ostream &stream, const A &o){
			for(size_t i=0;i<2*32;i++)  stream<< o[i];
		return stream;   
	}
};
int main(){ 
	srand(time(nullptr));

	A e; 
	for(size_t i=0;i<2*32;i++)
		e[i]=rand()%2; 
	e[0]=0;e[63]=0;
	cout<<"\n"<<e<<"\n";
	return 0;
}
	

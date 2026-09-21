 #include<iostream>
using namespace std;

class A{  
	int t[11][11]; 
	class B{
		int *data;
		public:
		int &operator[](size_t j){ 
			if(j>=11)throw 1;
			return data[j];
		}
		B(int *a){data =a;}
	};
	class B1{
		const int *data;
		public:
		const int &operator[](size_t j)const{ 
			if(j>=11)throw 2;
			return data[j];
		}
		B1(const int *a){data =a;}
		friend ostream &operator <<(ostream &stream, const B1 &o){
			try{    
				for(size_t i=0;i<18;i++)  
					stream<< o[i]<<" ";
			} catch(...) {}
			stream<<"\n";
		return stream;   
		}
	};
	public:
	B operator[](size_t i){if (i>=11) throw 0;return  B(t[i]);}
	
	B1 operator[](size_t i)const{if (i>=11) throw -1;return  B1(t[i]);}
	friend ostream &operator <<(ostream &stream, const A &o){
		try{    
			for(size_t i=0;i<18;i++)  stream<< o[i];
			 } catch(...) {}
		
		return stream;   
	}
};
int main(){ 
	srand(time(nullptr));
	A e; 
	for(size_t i=0;i<111;i++)
		try{ 
			for(size_t j=0;j<111;j++)
				e[i][j]=rand()%11; 
		}
		catch(...){}
	cout<<e;
	return 0;
}
	

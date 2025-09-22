#include<iostream>
using namespace std;
class vect{ 
	C *vector; //вектор (массив) комплексных чисел
	size_t size,//размер отведенной памяти (количество комплексных чисел, которые  можно разместить по указателю vector)
	n;//теккущий размер вектора, т.е. количество  загруженных в массив комплексных чисел
	public: vect (size_t size,size_t n){ //онструктор с параметрами
			this->size=size;
			this->n=n;
			vector=new C[size];//отвеедение памяти под массив
			for(size_t i=0;i<n;i++) //заполнение массива n случайными комплексными числами
				vector[i]=C((rand()%11-rand()%5)/2., (rand()%11-rand()%5)/2.);
	}
	vect(const vect &z){ //конструктор копии, необходим длясложного класса
		size=z.size; n=z.n; 
		vector=new C[size];//для копии объекта отводим новую память 
		for(size_t i=0;i<n;i++)
			vector[i]=z.vector[i]; //копиируем комплексные числа
	}
	 C& operator[](size_t i)const{// перегружаем оператор квадратные скобки
		return vector[i];
	}
	friend ostream &operator <<(ostream &stream, const vect &obj){//перегружаем оператор <<
		for(size_t i=0;i<obj.n;i++)
			stream<<obj.vector[i]<<" ";
		puts("");
		return stream;
	}
	~vect(){ //дестрруктор необходим для сложного класса
		delete []vector; 
		vector=nullptr;
	}
	vect& operator --(){ //оперратоор префиксный декремент,возврашает ссылку на преобразованный объект 
		if(n>0)
			n--;
		return *this;
	}
	vect operator --(int){ //оперратоор постпрефиксный декремент, возвращает объект после преобразованния
		vect tmp(*this);
		--(*this);
		return tmp;
	}
	vect& operator ++(){ //оператоор префиксный инкремент 
		if(size==n){
			vect tmp(*this);
			delete  []vector;
			size*=2;
			vector=new C[size];
			for(size_t i=0;i<n;i++)
				vector[i]=tmp[i];
		}
		n++;
		vector[n-1]=C(0,0);
		return *this;
	}
	vect operator ++(int){ //оперратоор постпрефиксный инккремент 
		vect tmp(*this);
		++(*this);
		return tmp;
	}

};
int main(){
	srand(time(nullptr));
	vect v(vect(4,3));
	cout<<"v="<<v<<"\n"<<"++v="<<++v<<"\n"<<"v++="<<v++<<"\n"<<"--v="<<--v<<"\n"<<"v--="<<v--<<"\n"<<"v="<<v<<"\n";
	return 0;
}
	

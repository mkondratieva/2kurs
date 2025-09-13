#include<iostream>
using namespace std;
class C{ //класс комплексное число
	double Re,Im; 
	public:
	C(double Re, double Im){
		this->Re=Re;this->Im=Im;
	} //конструктор с параметрами
	C operator +(const C &z){
		return C(Re+z.Re, Im+z.Im);
	}//оператор сложения
	C &sopr(){  //сопряжение
		Im=-Im;
		return(*this);
	} 
	friend ostream &operator <<(ostream &stream, const C &obj){
		stream<<obj.Re<<"+i"<<obj.Im<<" ";
		return stream;
	}
	 /*	
	//? operator ++(){......}//префиксный ++
	//? operator ++(int){.....} //постпрефиксный ++
	 */

};
int main(){ 

	cout<<(C(-9.,7.)+C(9.,-7.));
	cout<<C(8,8).sopr();
	C z(1,2);
//	cout<<z<<++z<<z<<z++<<z;     //тест инкремента
	return 0;
}
	

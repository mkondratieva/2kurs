#include<iostream>
using namespace std;
class complex{ //класс комплексное число
	double Re,Im;//у числа есть вещественная и мнимая части
	public:
	complex(){Im=Re=0.;} //конструктор без параметров, обнуляем поля класса
	complex(double Re, double Im){//конструктор с параметрами для рождения произвольного комплексного числа
		this->Re=Re;this->Im=Im;
	} 
	complex operator +(const complex &z){//сложение комплексных чисел
		return complex(Re+z.Re, Im+z.Im);
	}//оператор сложения
	void method(){  //сопряжение
		Im=-Im;
	} 
	friend ostream &operator <<(ostream &stream, const complex &obj){//печать числа
		stream<<obj.Re<<"+i"<<obj.Im<<" ";
		return stream;
	}

};
complex y(){return complex();} //функция, возвращающая комплексное число, без аргументов
void foo(){//x(y);//нельзя, х - локальная для main
}
int main(){ 
	cout<<complex(-9.,7.)+complex(9.,-7.)<<"\n";
	complex  z(8,8);cout<<z<<"\n";; 
	z.method();  cout<<z<<"\n";

	complex x(complex());//прототип функции, возвращающей комплексное число, аргументом которой является другая функция, возвращающая комплексное число без параметров
//прототип функции (в отличие от реализации) может находиться внутри функции, (локально)
	cout<<x(y)<<"\n"; //можно! вызов х

	return 0;
}
complex x(complex func()){return func();}	


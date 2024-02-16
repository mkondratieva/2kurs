#include <iostream> 
using namespace std;
struct Factory;
struct  Base {  //базовый класс 
	Base(){puts("constrBase");} //конструктор без параметров, по умолчанию он будет вызываться при создании объектов дочерних классов
	Base(int i){cout<<i;}//другой конструктор, для его вызова при создании объектов дочерних классов  его нужно привязать вручную
	virtual ~Base(){puts("~Base");} //деструктор, он будет вызван после деструктора дочернего класса
	void pr(){  
		foo();
	}
	virtual void foo()=0;//foo - чисто виртуальная функция, из чего следует, что Base -- абстрактный класс (объектов этого класса создать нельзя)
	static Base *create(int i, Factory**f);//Базовый класс не знает  ничего конкретного о своих потомках, но, т.к. он не запрещает наследование, то разрешено обращение к фабрикам (это не нарушает принцип ООП)
};
struct Child:Base{ //дочерний класс наследует все поля и методы Base
	Child():Base(111111){puts("constrChild");} //конструктор дочернего класса можно привязать к любому конструктору базового через список инициализации
	Child(const Base&){}//этот конструктор нужен в каждом дочернем классе для перегрузки оператора сложения
	~Child(){puts("~Child");}
	void foo()override{ //foo - виртуальный метод Child, все чисто виртуальные методы в дочернем классе должны быть определены
		puts("Child");
	}
};

struct Child1:Base{ //дочерний  класс 
	void foo()override{ 
		puts("Child1");
	}
	Child1(const Base&){}
	Child1(){}//если в классе есть хотя бы один конструктор, конструктор по умолчанию пропадает (а он нам нужен)
};
struct Factory{ //класс фабрика, повторяет иерархию обслуживаемых классов и предназначен для генерации объектов разных типов
    virtual Base *create()=0;
};//все, что нужно от фабрики,  этот метод, его аргументы зависят от конкретной задачи
struct Factory_child:Factory{
    virtual Base *create(){return new  Child;}//эта фабрика производит объекты класса Child
};
struct Factory_child1:Factory{
    virtual Base *create(){return new  Child1;} // ---||--- Child1
};   
Base *Base::create(int i, Factory**f){return f[i]->create();}
Child operator +(const Base&,const Base&){
        return Child();
}
int main(){
    Factory *f[2]={new Factory_child,new Factory_child1};//массив указателей на фабрики
	Base *array[5]; //массив указателей на базовый класс, в реальности некоторые из элементов массива указывают на объект дочернего класса, а некоторые  базового
	for(size_t i=0;i<5;i++){//заполняем массив
	        array[i]=Base::create(rand()%2,f);
	}
	Child x=*array[0];
    for(size_t i=1;i<5;i++)
		x=x+*array[i]; //находим сумму
	for(size_t i=0;i<5;i++)
		array[i]->pr(); 
	for(size_t i=0;i<5;i++)
		delete (array[i]);
	for(size_t i=0;i<2;i++)
		delete (f[i]);
    return 0;
}

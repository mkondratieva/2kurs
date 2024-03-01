#include <iostream> 
#include<fstream>
#include<sstream>
#include<vector>
using namespace std;
struct Factory;
struct  Base:string {//базовый класс отнаследован от string , в строке будем хранить имя выходного файла
       	Base(const string&s):string(s){}//конструктор с параметром
        Base(const Base&)=default;
        Base(Base&&)=default;
        Base& operator=(const Base&)=default;
        Base& operator=(Base&&)=default;
        virtual ~Base()=default; //деструктор
        virtual void pr()=0;
	static Base *create(const string &, Factory**f);//Базовый класс не знает  ничего конкретного о своих потомках, но, т.к. он не запрещает наследование, то разрешено обращение к фабрикам (это не нарушает принцип ООП)
	Base &operator ++(){ //префиксная форма возвращает ссылку на базовый класс, что возможно для абстрактного класса
        	this->insert(0,"!");
        	return *this;
    }
};
struct Child:Base{ //дочерний класс наследует все поля и методы Base
	Child(const string &s):Base(s){} 
	Child(const Base&v):Base(v){}//этот конструктор нужен в каждом дочернем классе для перегрузки оператора сложения и постфиксной формы инкремента
	void pr(){//виртуальный метод Child, все чисто виртуальные методы в дочернем классе должны быть определены
		puts("Child");
                ofstream out(*this,ios::app);//открываем файл с именем, записанном в string, на дозапись
                out<<"Child\n"; //выводим что-то в файл
	}
};
struct Child1:Base{ //дочерний  класс 
	void pr(){ 
		puts("Child1");
                ofstream out(*this,ios::app);
                out<<"Child1\n";
	}
	Child1(const Base&v):Base(v){}
	Child1(const string &s):Base(s){}
};
struct Factory{ //класс фабрика, повторяет иерархию обслуживаемых классов и предназначен для генерации объектов разных типов
        virtual Base *create(const string &)=0;
	virtual ~Factory(){}
};//все, что нужно от фабрики,  этот метод, его аргументы зависят от конкретной задачи
struct Factory_child:Factory{
	virtual Base *create(const string &s){return new  Child(s);}//эта фабрика производит объекты класса Child
};
struct Factory_child1:Factory{
	virtual Base *create(const string &s){return new  Child1(s);} // ---||--- Child1
};   
Base* Base::create(const string &s,Factory**f){
	stringstream ss(s);
	int Type; //в s сначала записано число 0 или 1 (указывает, объект какого дочернего класса строить), а затем имя файла для вывода
	ss>>Type; //извлекаем из строки 0 или 1
	string buf; ss>>buf; //имя файла
	if(Type==0)
        	return  f[0]->create(buf);
	return  f[1]->create(buf);
}
Child operator +(const Base&,const Base&){
        return Child("++++++");
}
Child operator++(Base &b,int){
	Child tmp(b);
	b.insert(0,"!");
	return tmp;
}
int main(){
	Factory *f[2]={new Factory_child,new Factory_child1};//массив указателей на фабрики
	vector<Base *>array; //вектор указателей на базовый класс, в реальности некоторые из элементов массива указывают на объект дочернего класса, а некоторые  базового
	ifstream  in("input.txt");
	string buf;
	while(getline(in,buf))//перебор строк входного файла
                array.push_back(Base::create(buf,f));//по извлеченной из файла строке с помощью фабрик строим объект дочернего класса, указатель на который кладем в вектор array
	Child x(*array[0]);
	for(size_t i=1;i<array.size();i++)
		x=x+*array[i]; //находим сумму
	x.pr();
	for(size_t i=0;i<array.size();i++) //здесьнужно будет использовать итератор повектору
		array[i]->pr();//печать в выходные файлы объектов дочерних классов
	for(size_t i=0;i<array.size();i++)
		*array[i]=++(*array[i])++;//один из возможных тестов на ++
	for(size_t i=0;i<array.size();i++)
		array[i]->pr(); 
	for(size_t i=0;i<array.size();i++)
		delete(array[i]); 
	for(size_t i=0;i<2;i++)
		delete (f[i]);
	 return 0;
}

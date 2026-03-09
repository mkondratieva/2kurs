#include <iostream>
#include<memory>
using namespace std;
#define N 7
struct Factory;
struct Person {
	int age;
	Person(int i):age(i){} 
	virtual void pr()=0;
	virtual void operator ++(){age++;if(age>66)throw 0;}
	virtual ~Person(){}
	void operator==(const Person&){}//наследуется, в отличии от =
	 Person (const Person &v){age=v.age;}
	virtual Person & operator=(const Person &v){age=v.age;return *this;} //НЕ НАСЛЕДУЕТСЯ
	static shared_ptr<Person>create(int ,shared_ptr<Factory> *);//родительский  класс ничего не знает о своих наследниках, но допускает наличие фабрик, их производящих
};
struct Student:Person{ 
	Student(int i):Person(i){}
	Student(const Person &per):Person(per){}//конструктор копии по const-ссылке на базовый класс
//как перегрузить  move-конструктор по rvalue-ссылке на базовый класс?
	virtual void pr(){
		cout<<" Student  "<<age<<"\n"; 
	}
	void operator ++(){age++;if(age>30)throw 1;}
};
struct Specialist:Person{
	Specialist(int i):Person(i){} 
	virtual void pr(){
		cout<<" Specialist  "<<age<<"\n"; 
	}
	Specialist(const Person&per):Person(per){}
	virtual void operator ++(){age++;if(age>66)throw 0;}
};
Specialist operator++(Person &z,int){Specialist tmp(z); ++z; return tmp;}//постфиксный ++ не может возвратить объект родительского класса, т.к. класс абстрактный

struct Factory{virtual shared_ptr<Person> create()=0; //повторяет иерархию классов
	virtual ~Factory(){}
};
struct FactoryStudent:Factory{//производит умные указатели на объекты дочернего класса Student
	shared_ptr<Person> create(){return make_shared<Student>(13+rand()%20);}
};
struct FactorySpecialist:Factory{//производит умные указатели на объекты дочернего класса Specialist
	shared_ptr<Person> create(){ return make_shared<Specialist>(rand()%99);}
};
shared_ptr<Person>Person::create(int i,shared_ptr<Factory> f[]){
	return  f[i%2]->create();
} 
int main(){ 
	shared_ptr<Person> p[N]; 
	shared_ptr<Factory> f[2]={make_shared<FactoryStudent>(),
	make_shared<FactorySpecialist>()};
	for(size_t i=0;i<N;i++){ 
		p[i]=Person::create(i,f);
	}
	for(size_t i=0;i<N;i++) 
		p[i]->pr();
	puts("");
	for(size_t i=0;i<N;i++)
		try{ 
			++*p[i];(*p[i])++;
		} 
		catch(...){
			if(dynamic_pointer_cast<Student>(p[i]))
				p[i]=make_shared<Specialist>(p[i]->age); 
			else p[i]=nullptr;
		} 
	size_t count=0;for(size_t i=0;i<N;i++)if(p[i])p[count++]=p[i];//2 бегунка, удаляем выбывших
	for(size_t i=0;i<count;i++) 
		p[i]->pr();
	puts("");
	shared_ptr<Person> a; 
	a=make_shared<Student>(-2);
	*a=*p[0];
	for(size_t i=0;i<count-1;i++)
		try{*p[i]=*p[i+1]; }
		catch(...){ 
			p[i]=make_shared<Specialist>(p[i+1]->age); }
	*p[count-1]=*a;

	Student s(0);Specialist  b(0);
	s=b;//= не наследуется их базового класса, но будет работать при наличии в дочерних классах конструктора копии по ссылке на базовый класс
	s==b; //== наследуется
	s++;++s;b++;++b;  //работает на lvalue объектах
	++move(s);//префиксный работает  и на rvalue
	//move(s)++;//постфиксный не работает   на rvalue
	//что нужно добавить в сигнатуру классов, чтобы он работал?
	for(size_t i=0;i<count;i++) 
		p[i]->pr();
	return 0;
}
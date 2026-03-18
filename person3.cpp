#include <iostream>
#include<memory>
using namespace std;
#define N 7

struct Factory;
struct Person {
	string name;
	int age;
	Person(int i):name("Ivanov"),age(i){} 
	virtual void pr()=0; 
	virtual void operator ++(){age++;if(age>66)throw 0;}
	virtual  ~Person()=default;
	Person(const Person &v)=default;
	Person(Person &&)=default;
	virtual Person & operator=(const Person &)=default;//т.к. кдасс сожержить string, копирующий оператор присваивания по умолчанию может выбрость исключение (при выхове new)
	virtual Person & operator=(Person &&per) //default operator является npexcept, поэтому, если в Student хотим выбрасывать исключение, нужно задать явно
	{  
		age=per.age;name=move(per.name);return *this;
	}
	static shared_ptr<Person>create(int ,shared_ptr<Factory> *);//родительский  класс ничего не знает о своих наследниках, но допускает наличие фабрик, их производящих
};
struct Student:Person{ 
	Student(int i):Person(i){}
	Student(const Person &per):Person(per){ 
		if(per.age>33) throw -1;
	}
	Student(Person &&per):Person(move(per)){ 
		if(per.age>33) throw -1;
	}
	virtual void pr(){
		cout<<" Student  "<<age<<"\n"; 
	}
	void operator ++(int){age++;if(age>30)throw 1;} //для Student(0)++

	Person& operator =(const Person &per)override{
        	if(per.age>33) throw 1;
	        Person::operator=(per);
        	return *this;
	}
	Person& operator =(Person &&per)override{
		if(per.age>33) throw 1;
        	Person::operator=(std::move(per));
        	return *this;
	}
	void operator ++()override{age++;if(age>30)throw 1;}
};
struct Specialist:Person{
	Specialist(int i):Person(i){} 
	virtual void pr(){
		cout<<" Specialist  "<<age<<"\n"; 
	}
	Specialist(const Person&per):Person(per){}
	Specialist(Person&&per):Person(move(per)){} 
	void operator ++()override{age++;if(age>66)throw 0;}
};
Specialist operator++(Person &z,int){Specialist tmp(z); ++z ; return tmp;}
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
			++*p[i];(*p[i])++; //увеличили возраст
		} 
		catch(...){
			if(dynamic_pointer_cast<Student>(p[i]))
				p[i]=make_shared<Specialist>(p[i]->age); 
			else p[i]=nullptr;
		} 
	size_t count=0;
	for(size_t i=0;i<N;i++)if(p[i])p[count++]=p[i];//2 бегунка, удаляем выбывших
	puts("");
	for(size_t i=0;i<count;i++) 
		p[i]->pr();
	puts("");
	Specialist a(*p[0]); //циклический сдвиг
	for(size_t i=0;i<count-1;i++)
		try{
			*p[i]=move(*p[i+1]); // *p[i]=*p[i+1];
		}
		catch(...){  //если при сдвиге студент получил возраст вне допустимого диапазона, выбрасываем исключение
			p[i]=make_shared<Specialist>(p[i+1]->age); } //если выброшено исключение, студента переводим в специалиста
	*p[count-1]=move(a); //здесь тоже надо ловить исключение
	Specialist  b(11);
        Student s(b);
	s=b;
	s++;++s;b++;++b; 
	++move(s);
	move(s)++;   Student(8)++;
	puts("");
	for(size_t i=0;i<count;i++) 
		p[i]->pr();
{
	puts("move test 1: direct-init");
	Student stud(25);
	Specialist spec(std::move(stud));
	cout << spec.name << '\n' << stud.name << '\n'; //Ivanov выводится 1 раз
	}
{	puts("move test 2: copy-init");
	Student stud(25);
	Specialist spec=move(stud);
	cout << spec.name << '\n' << stud.name << '\n'; //Ivanov выводится 1 раз
}
{	puts("move test 3: move=");
	Student stud(25);
	Specialist spec(42);
	spec=move(stud);
	cout << spec.name << '\n' << stud.name << '\n';  //Ivanov выводится 1 раз
}
	Specialist t(9);
	t=Student(9); //move=
	return 0;
}
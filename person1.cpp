#include <iostream>
#include<memory>
using namespace std;
#define N 7

struct Person {
	int age;//в полиморфном классе перед age ьудет скрытое поле, ссылка на таблицу виртуальных функций 
	Person(int i):age(i){} 
	virtual void pr(){
		cout<<" Person  "<<age<<"  "<<((void **)this)[0]<<"  "<<((int *)this)[2]<<"\n"; //печать из-под капота ссылки на таблицу виртуальных функций и age
	}
	virtual void operator ++(){age++;if(age>66)throw 0;}
	virtual ~Person(){}
};
struct Student:Person{ 
	Student(int i):Person(i){}
	void pr()override{
		cout<<" Student "<<age<<"  "<<*(void **)this<<"  "<<((char ****)this)[0][-1][1]<<"\n"; //печать из-под капота ссылки на таблицу виртуальных функций и имени класса
	}
	void operator ++(){age++;if(age>30)throw 1;}
};
int main(){ 
	shared_ptr<Person> p[N];
	for(size_t i=0;i<N;i++){ 
		if(i%2)
			p[i]=make_shared<Person>(rand()%99); 
		else 
			p[i]=make_shared<Student>(20+rand()%13);
	}
	for(size_t i=0;i<N;i++) 
		p[i]->pr();//ОТМЕЧАЕМ, ЧТО ТАБЛИЦЫ ВИРТУАЛЬНЫХ ФУНКЦИЙ ОДИНАКОВЫ ДЛЯ ОБЪЕКТОВ ОДНОГО КЛАССА, НО РАЗНЫЕ ДЛЯ ОБЪЕКТОВ РАЗНЫХ КЛАССОВ
	puts("");
	for(size_t i=0;i<N;i++)
		try{ ++*p[i];} 
		catch(...){
			if(dynamic_pointer_cast<Student>(p[i]))
				p[i]=make_shared<Person>(p[i]->age); 
			else p[i]=nullptr;
		} 
	size_t count=0;for(size_t i=0;i<N;i++)if(p[i])p[count++]=p[i];
	for(size_t i=0;i<count;i++) 
		p[i]->pr();//ОТМЕЧАЕМ, ЧТО В ТАБЛИЦЕ ВИРТУАЛЬНЫХ ФУНКЦИЙ ЗАПИСАНО ИМЯ КЛАССА

	return 0;

}
#include <iostream>
#include<memory>
#include <string>
using namespace std;
#define N 7

struct Person {
	int age; 
	Person(int i):age(i){} 
	virtual void pr(){//эта функция может (но не обязана) быть перегружена в дочерних классах
		cout<<" Person "<<age;
	}
	void operator ++(){age++;}
	virtual ~Person(){}//нужно понимать, почему без такого деструктора код может не скомпилироваться
};
struct Student:Person{  
	Student(int i):Person(i){}//каждый конструктор дочернего класса должен быть привязан к какому-то конструктору базового
	void pr()override{//override не обязательно, для самоконтроля (перегрузка виртуального метода)
		cout<<" Student "<<age;
	}
};
int main(){ 
	shared_ptr<Person> p[N];//массив умных указателей на базобвый класс
	for(size_t i=0;i<N;i++){ //в этом цикле необходимо вручную заполнить массив так, чтобы  присутствовали указатели как на базовый, так и на дочерний классы.
		if(???)
			p[i]=make_shared<Person>(???); 
		else 
			p[i]=make_shared<Student>(???);
	}
	for(size_t i=0;i<N;i++) 
		p[i]->pr(); //тест заполнения
	puts("");
	for(size_t i=0;i<N;i++)
		++*p[i]; 
	for(size_t i=0;i<N;i++) 
		p[i]->pr();
	puts("");
	return 0;
}
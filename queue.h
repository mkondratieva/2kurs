#include <iostream>    //реализация  кольцевой очереди на базе массива
#include<cstdlib>
#include<ctime>
using namespace std;
template <class T=int>  //шаблон очереди, по умолчанию очередь целых чисел
class queue{
	T* body; //массив для хранения элементов очереди
	int head,tail,Maxsize; //индекс головы, хвоста и глубина очереди
	int next  (int)const; //индекс, следующий для текущего, нужен чтобы закольцевать очередь
	public:
	queue(int n){ //создание пустой очереди заданной глубины
		Maxsize=n+1; //т.к. в реализации не будем хранить фактический размер очереди, одно место в массиве должно оставаться свободным, иначе нельзя отличить пустую очередь от полностью заполненной
		head=tail=0; //в пустой очереди голова совпадает с концом, их значения могут быть любыми
		body=new T[Maxsize]; //n->Maxsize!!!!!!!!!!!!!!! исправить, чтобы в очередь можно было положить количество элементов, равное ее глубине
	}
	queue(const  queue<T> &q){ //конструктор копии для сложного класса
		Maxsize=q.Maxsize;
		head=q.head;
		tail=q.tail;
		body=new T[Maxsize];
		for(int i=0;i<Maxsize;i++)
			body[i]=q.body[i];
	}
	int push(const T &v){//возвращает флаг успешности операции добавления в очередь
		return next(tail)==head?0:(body[tail]=v,tail=next(tail),1); //tail -- индекс свободной ячейки для добавления элемента в очередь
//очередь полностью заполнена, если после добавлении элемента на это место хвост совпадет с головой (а это для нас пустая очередь) 
	}
	int pop( T &v){//возвращает флаг успешности операции удаления головы очереди (удаленный элемент сохраняется в аргументе
		return tail==head? 0:(v=body[head],head=next(head),1);//начало непустой очереди находится по индексу head
	}
	~queue(){
		delete []body;
	}
	class iterator{
		const   queue *q;int cur;
		public:
		iterator(const   queue *q, int cur){
			this->q=q;
			this->cur=cur;
		}
		void operator ++(){
			cur=q->next(cur);    
		}
		T& operator *(){
			return q->body[cur];
		}
		int operator !=(const iterator &q)const {
			return  this->cur!=q.cur;
		}
	};
	iterator begin()const{
		return iterator(this,head);
	}
	iterator end ()const{
		return iterator(this,tail);
	}

};
template<class T>
void pr(queue<T> q) { //печать элементов очереди в прямом порядке (сначала первый из загруженных)
		T x;
		while(q.pop(x)) //цикл работает, пока в очереди есть элемент
			cout<<x<<" "; //печатаем извлеченный элемент, в классе T должен быть перегружен оператор <<
	}
template<class T>
int queue<T>::next(int pos)const {
		return pos==Maxsize-1?0:pos+1;
} 		



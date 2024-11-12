#include<iostream>
#include<memory>
using namespace std;
using T=int;
class stack{ 
	T *body;  
	size_t Maxsize,top;
	public:
	stack(size_t n){
		Maxsize=n;
		top=0;	
		body=new T[n];
	}
	~stack(){
		delete []body;
	}
	stack(const  stack &other){
		Maxsize=other.Maxsize;
		top=other.top;
		body= new  T[Maxsize];
	}
	size_t push(T t){
		return top==Maxsize? 0:(body[top]=t,++top);
	}
	size_t pop(T &t){
		return top==0? 0:(t=body[top-1],top--);
	}
	class iterator{
		const stack *q; size_t cur;
	public:
		iterator(const stack *q, size_t cur=0){
			this->q=q;
		this->cur=cur;
		}
		void operator ++(){
			cur++;
		}
		T& operator *(){
			return q->body[cur];
		}
		bool operator !=(const iterator&other){
			return cur!=other.cur;
		}
		
	};
	iterator begin(){return iterator(this);}
	iterator end(){
		return iterator(this,top);
	}
};
int main(){ 
	stack q(11),h(q);
	T z;
	while(q.push(rand()%11));
	for(auto a :q)cout<<a<<" ";
	puts("");
	while(q.pop(z))
		h.push(z);
	for(auto a :h)cout<<a<<" ";
	puts("");
	for(auto &a :h) a=88;
	for(auto a :h)cout<<a<<" ";
	puts("");
	return 0;
}
	

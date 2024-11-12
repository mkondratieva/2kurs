#include<iostream>
#include<memory>
#include<fstream>
using namespace std;
using T=string;
class queue{ 
	T *body;  
	size_t Maxsize,head,tail;
	size_t next(size_t cur)const {return cur==Maxsize-1? 0:cur+1;}
	public:
	queue(size_t n){
		Maxsize=n;
		head=tail=0;	
		body=new T[n];
	}
	~queue(){
		delete []body;
	}
	size_t push(T t){
		return next(tail)==head? 0:(body[tail]=t,tail=next(tail),1);
	}
	size_t pop(T &t){
		return head==tail? 0:(t=body[head],head=next(head),1);
	}
	class iterator{
		const queue *q; size_t cur;
	public:
		iterator(const queue *q, size_t cur=0){
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
	iterator begin(){return iterator(this,head);}
	iterator end(){
		return iterator(this,tail);
	}
	
};
int main(){ 
	queue q(5);
	ifstream in("1.txt");
	T x;
	while(getline(in,x))
		q.push(x);
	for(auto a :q)cout<<a<<"\n";
	puts("");
	return 0;
}
	

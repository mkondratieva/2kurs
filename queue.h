#include <iostream>
#include<fstream>
using namespace std;
using  Type= string ;
class queue{
    	Type *body; 
	int head, tail, Maxsize; 
	int next(int pos)const{
		return pos==Maxsize-1? 0:pos+1;
	}
public:	queue(int n){
		Maxsize=n+1;
		head=tail=Maxsize-1;
		body= new Type [Maxsize];
	}
	~queue(){delete []body;}
	int push(const Type &v){
   		 return next(tail)==head?0:(body[tail]=v,tail=next(tail),1);
	}
	int pop(Type&x){ 
	        return head==tail?0:(x=body[head],head=next(head),1);
	}
	class iterator{ 
		const queue *q;
		int cur; 
	public: iterator(const queue *q,int cur){
			this->q=q; 
			this->cur=cur;
		}
		void operator ++(){ 
			cur=q->next(cur);
		}
		Type & operator *(){ 
			return q->body[cur];
		}
		int operator !=(const iterator &other){ 
			return  cur!=other.cur;
		}
	};
	iterator begin()const{ 
		return iterator(this,head);
	}
	iterator end ()const {    
		return iterator(this,tail);
	}
};

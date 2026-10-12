#include <iostream>
#include<time.h>
using namespace std;
using Type = int;

class stack{
	Type *body;
	int top,
    	Maxsize;
	public:	stack (int n){
	    	Maxsize=n;
    		top=0;
		body= new Type [n];
	}
    	~stack(){
		delete []body;
	} //+???
    	int push (const Type &v){
	    return top==Maxsize?0: (body[top]=v, ++top);
	}
    	int pop(Type &v){
    		return top?(v=body[top-1], top--):0;
	}
	class iterator{ 
		const stack *q;
		int cur; 
	public: iterator(const stack *q,int cur=0){
			this->q=q; 
			this->cur=cur;
		}
		void operator ++(){ 
			cur++;
		}
		Type & operator *(){ 
			return q->body[cur];
		}
		int operator !=(const iterator &other){ 
			return  cur!=other.cur;
		}
	};
	iterator begin()const{return iterator(this);}
	iterator   end ()const {return iterator(this,top);  
	}
};

int main(){ 
	srand(time(NULL)); int n=11;
	stack q(n); 
	int k; 
	do{  
		k=rand()%10; 
	}
	while(q.push(k)) 
		;
	for(auto it=q.begin();it!=q.end();++it)
		cout<<*it<<" ";
	puts("");
	Type u; 
	stack  tmp(n),tmp1(n);
	while(q.pop(u))
		tmp.push(u);
	while(tmp.pop(u))
		tmp1.push(u);  
	while(tmp1.pop(u))
		q.push(u);  
	for(auto i:q)
		cout<<i<<" ";	
	puts("");
	for(auto it=q.begin();it!=q.end();++it)
		*it=0;
	for(auto it=q.begin();it!=q.end();++it)
		cout<<*it<<" ";
	puts("");

	return 0;
}


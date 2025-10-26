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
	}
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
	iterator begin()const{ return iterator(this);}
	iterator   end ()const { return iterator(this,top);  
	}
};

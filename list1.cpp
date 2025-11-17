#include <iostream>
#include <memory>
using namespace std;
using T= int;
class List{    
	class Node{    
		shared_ptr<Node> next=nullptr//,prev=nullptr // вариант 1
		;
    		std::weak_ptr<Node> prev; //вариант 2
    	        T data;
		public:	
		Node(T v){data=v;}
		friend class List;
	};
	shared_ptr<Node> head=nullptr,cur=head;
	public:
	~List(){  return;  //small smart вариант 2
				while(1){  //вариант 1 + для списков большого размера вариант 2
					auto u=head->next;
					if(!u)break;
					head->next=head->next->next;
  					u->next=nullptr;
					//u->prev=nullptr; // вариант 1
			}	

	}
	void push(T v){
		if(!head){
			head=make_shared<Node>(v); 
			cur=head; 
			return;
		}
		auto u=cur->next;  
		cur->next=make_shared<Node>(v); 
		cur->next->prev=cur;
		if(u)u->prev=cur->next;
		cur->next->next=u;
	}
	void gotonext(){
		if(cur->next)
			cur=cur->next;
	}
	void pr(){
		if(!head)return;
		auto a=head;  
		while(a){
			cout<<a->data<<" ";
			a=a->next; 
		}
	}
	void pr_back(){
		if(!head)return;
		auto a=head;
		while(a->next)
			a=a->next; 
		while(a){
			cout<<a->data<<" ";
			//a=a->prev; //вариант 1
			a=a->prev.lock(); //вариант 2

		} 
	}

};
int main(void) { 
	{
	List l;
	for(int i=0;i<12//*32222
;i++) {
		 l.push(i); l.gotonext();
		}
	l.pr(); puts("");  l.pr_back();
	}                 
	puts("end");

}
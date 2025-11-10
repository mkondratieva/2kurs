#include<iostream>
#include<memory>
using namespace std;
using Type=int;
struct List{ 
	struct Node{
		//Node *next=nullptr; //обычная ссылочная реализация списка
		shared_ptr<Node> next=nullptr;  //реализация через умныый указатель
		Type data;
		~Node(){
			delete next;  //ДЛЯ НЕБОЛЬШИХ СПИСКОВ
			return;      //-------------
	 		while(1){  //для списков большого размера   цик
				auto u=next;
				if(!u)break;
				//............
		//		delete u;      //??
		}
	}
	friend class List;
	};
//	Node *head=nullptr,*cur=head;
	shared_ptr<Node> head=nullptr,cur=head;
	~List(){//delete head;
	}
	void push(Type v){
		if(!head) {  //если список пуст
		//	head=cur=new Node;
			head=cur=make_shared<Node>();  //?
			head->data=v;   
			return ;
		}
		auto u=cur->next;
		//cur->next=new Node;  
		cur->next=make_shared<Node>(); 
		//.........  
 	}
	int pop(Type &);//удаление по стрелке next
	void gotonext(){ cur=cur->next;  }
	class iterator{
		List *l;   //Node *cur;
\		shared_ptr<Node> cur;
		public: 
		iterator(List *l,shared_ptr<Node> cur=nullptr
//Node *cur=nullptr
			){
			this->l=l; this->cur= cur; 
		}	
		void operator++ (){ 
			cur=cur->next;;
		}
		int operator !=(const iterator &v){
			return cur!=v.cur;
		}
		Type & operator *(){ 
			return 	cur->data;
		}
	};
	iterator begin(){ 
		return iterator(this,head);
	}
	iterator end(){ 
		return iterator(this);
	}
};
int main(){ 
	auto p1=make_shared<List::Node>(); auto p2=make_shared<List::Node>();
	p1->next=p2;p2->next=p1;//циклическая ссылка
	p1->next=nullptr;  //без этого утечки
	{
		List list; 
		for(size_t i=0;i<12//*32222
			;i++){
			list.push(i); if(i>0)list.gotonext();
		}
		for(auto it:list)cout<<it<<" " ;
	}

		puts("end");
	return 0;
}
	

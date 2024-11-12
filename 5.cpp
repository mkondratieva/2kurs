#include<iostream>
#include<memory>
using namespace std;
class List{ 
     class Node{
//   Node * next=nullptr;
    shared_ptr<Node> next=nullptr;
    friend class List;
    public:
    ~Node(){ //delete next;
             //return;
            	while(1){
                	auto u=next;
                	if(!u) break;
                	next=next->next;
                	u->next=nullptr;//чтобы исключить рекурсию
            		//delete u;
	         }
	    }
    };
    shared_ptr<Node> //Node*
    head=nullptr;
    public:
    ~List(){//delete head; 
    }
    void push(){
        if(!head){
           //head=new Node; 
            head=shared_ptr<Node>(new Node); 
            return;
        }
        auto u=head->next;
	//head->next=new(Node);
        head->next=shared_ptr<Node>(new Node);
        head->next->next=u;
    }
};
int main(){
/*  auto p=shared_ptr<List::Node>(new(List::Node));
    auto p1=shared_ptr<List::Node>(new(List::Node));
    p->next=p1; p1->next=p;//циклическая зависимость
    p->next=nullptr;//как ее можно исправить (разорвать)
 
    int *p=new int;delete p; p=new int;    delete p;
    auto p1=shared_ptr<int>(new int);
    p1=shared_ptr<int>(new int);p1=shared_ptr<int>(new int);
    cout<<sizeof(p)<<"  "<<sizeof(p1)<<"\n";
    */
    {
    List list;
    for(size_t i=0;i<2*32222;i++)  //с большим списком с умными указателями деструктор по умолчанию не работает 
//(также, как список с обычними указатлями и рекурсивным деструктором)
         list.push();
    }
    puts("end");
    return 0;
}
	

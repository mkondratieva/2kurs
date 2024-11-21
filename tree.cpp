#include <iostream>
#include <memory>
using namespace std;
class Tree{     
class Node{     
		int key;
		shared_ptr<Node> left=nullptr,right=nullptr;
	public:		
		Node(int key){this->key=key;}
		void push(int key){
			auto u=shared_ptr<Node>(new Node(key)); 
			if(key<this->key&&left) {left->push(key);return;}
			if(key>=this->key&&right) {right->push(key);return;}
			if(key<this->key)left=u;
			else right=u;
		}
		void pr(){
			if(left)
				left->pr();
			cout<<key<<" ";
			if(right)
				right->pr();
		}
		friend class Tree;
	};
	shared_ptr<Node>  root=nullptr;
	public:
		void push(int key){
		if(!root)
			root=shared_ptr<Node>(new Node(key));
		else root->push(key);
	}
	void pr(){
		if(root)
			root->pr();
	}
};

int main(void) { 
	{
	Tree l;l.push(1);l.push(-2);//
	l.push(-42);
	l.push(32);
	l.push(-22);
	l.push(22);
	l.push(12);
	l.pr();

	for(size_t i=0;i<1//2//8
		*11111
		;i++) 
		l.push
//(rand()%1000-500); //
(i);
	}
	puts("end");
	return 0;
}
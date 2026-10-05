#include<iostream>
#include<memory>
using namespace std;
class B{ 
	public:
	shared_ptr<int[]> u;
	B(){
		u= make_shared<int[]>(1);
		u[0]=9;
	}
	void method(){
		u= make_shared<int[]>(1);
		u[0]=-1;
	}
	friend ostream &operator <<(ostream &stream, const B &obj){
		stream<<obj.u[0];
		return stream;
	}
};

class A{ 
	public:
	shared_ptr<unique_ptr<int[]>> u;
	A(){
		u=make_shared<unique_ptr<int[]>>(new int[1]);
		(*u)[0]=9;
	}
	void method(){
		auto w=unique_ptr<int[]>(new int[1]);
		w[0]=-1;
		//swap(*u,w);
		*u=move(w);
	}
	A copy() const{
	    	A tmp;
		(*tmp.u)[0]=(*u)[0];
		return tmp;
	}
	friend ostream &operator <<(ostream &stream, const A &obj){
		stream<<(*obj.u)[0];
		return stream;
	}
};
int main(){
	unique_ptr<int[]> u,u1; 
	u=unique_ptr<int[]>(new int[11]);
	u[0]=1;         
	u1=move(u); //u1=u нельзя
	cout<<u1[0]<<"\n";  // u[0] нельзя
	puts("_______________");

	auto s= make_shared<int[]>(1);
	auto s1=s;
	s[0]=-1;         
	cout<<s[0]<<"  "<<s.use_count()<<" "<<s1[0]<<" "<<s1.use_count()<<"\n";  // u[0] нельзя
	puts("_______________");


	B a,b;
	a=b;
	cout<<a<<" "<<a.u.use_count()<<"  "<<b<<"  "<<b.u.use_count()<<"\n";
	a.method();
	cout<<a<<" "<<a.u.use_count()<<"  "<<b<<"  "<<b.u.use_count()<<"\n";

	puts("_______________");


	A z,v,w;
	z=v;
	w=z.copy();
	cout<<z<<" "<<z.u.use_count()<<"  "<<v<<" "<<v.u.use_count()<<"  "<<w<<"  "<<w.u.use_count()<<"\n";
	z.method();
	cout<<z<<" "<<z.u.use_count()<<"  "<<v<<" "<<v.u.use_count()<<"  "<<w<<"  "<<w.u.use_count()<<"\n";

	return 0;

}
	

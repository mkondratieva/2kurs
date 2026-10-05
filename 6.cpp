#include<iostream>  //matrix
#include<memory>
using namespace std;
class A{ 
	public:
	shared_ptr<unique_ptr<unique_ptr<int[]>[]>> u;
	A(){
		u=make_shared<unique_ptr<unique_ptr<int[]>[]>>(new unique_ptr<int[]>[1]);
		(*u)[0]=unique_ptr<int[]>(new int[1]); 
		(*u)[0][0]=9;
	}
	void method(){
		auto w=unique_ptr<int[]>(new int[1]);
		w[0]=-1;
		//swap(*u,w);
		(*u)[0]=move(w);
	}
	A copy() const{
	    	A tmp;
		(*tmp.u)[0][0]=(*u)[0][0];
		return tmp;
	}

	friend ostream &operator <<(ostream &stream, const A &obj){
		stream<<(*obj.u)[0][0];
		return stream;
	}

};

int main(){
	A z,v,w;
	z=v;
	w=z.copy();
	cout<<z<<" "<<z.u.use_count()<<"  "<<v<<" "<<v.u.use_count()<<"  "<<w<<"  "<<w.u.use_count()<<"\n";
	z.method();
	cout<<z<<" "<<z.u.use_count()<<"  "<<v<<" "<<v.u.use_count()<<"  "<<w<<"  "<<w.u.use_count()<<"\n";

	return 0;

}
	

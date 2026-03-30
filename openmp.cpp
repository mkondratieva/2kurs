#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<iostream>
#include<ctime>
#include <chrono>

using namespace std;

struct MyClass{  
	int n;   
	MyClass(int i):n(i){}
	MyClass():n(0){}
	MyClass operator +(const MyClass&ob)const{
		return MyClass(n+ob.n);
	} 
};

#pragma omp declare reduction(+: MyClass :omp_out= omp_out + omp_in) \
                    initializer(omp_priv = MyClass())

int main(){
//omp_set_num_threads (1);  // для непараллельного варианта
	srand(time(NULL));
	#pragma omp parallel for //простое распараллеливание цикла (на усмотрение компилятора), годится для циклов без зависимоси по данным, т.е. с независимыми итерациями, можно явно указать количество потоков      num_threads(3)
 	for(int i=0; i<10; i++)
   		printf("i=%d number_thread=%d\n",i,omp_get_thread_num());

	int s=0,k=10000;
	for(int i=0; i<k; i++){
		s=s+i;
	}
	printf("%d =true\n",s);
        s=0; 
	#pragma omp parallel for //неправильное распараллеливанеие, при котором возможна гонка потоков    // reduction(+:s)
 	for(int i=0; i<k; i++){
		s=s+i;
	}
	printf("%d =gonka\n",s);

	MyClass **data=new MyClass *[k],my_object(0);
	for(int i=0;i<k;i++)data[i]=new MyClass(i);

	#pragma omp parallel for reduction(+: my_object)  //если версия openmp позволяет использовать reduction для перегруженных операторов
	for (int i = 0; i < k; ++i) 
	    my_object=my_object+ *data[i]; 

	printf("my_objct=%d\n",my_object.n);

	s=0; int s1=0;
	#pragma omp parallel  sections   shared(s,s1)//правильно распараллеленный на 2 потока цикл
	{  
		#pragma omp  section 
		for(int i=0; i<k/2; i++){
			s=s+i;
		}
		#pragma omp  section  
        	for(int i=k/2; i<k; i++){
			s1=s1+i;
		}
	}
	printf("%d =sections\n",s+s1);

	s=0;
	#pragma omp parallel  //правильно распараллеленный на произвольное число потоков цикл
    	{   
        	int loc_sum =0;
	        #pragma omp for
       		for (int i=0;i<k;i++)
	            loc_sum = loc_sum + i;
	        #pragma omp critical //эта процедура выполняется всеми потоками, но не одновременно, поэтому гонки нет
               	s = s + loc_sum;
	}
	printf("%d =critical\n",s);
	int i=0; 
	#pragma omp parallel  shared(i) //пример кода с параллельными регионами, с непредсказуемыми результатами
	{
		int k=0;  //каждый поток заводит свою переменную k (она приватная)
		for( ;i<1;) {//каждый поток выполняет этот цикл, i -- разделяемая (общая) переменная, каждый поток может ее изменять
			k++; //если поток зашел в тело цикла, он увеличивает свою k
	//		#pragma omp barrier //барьер -- средство синхронизации между потоками. В этой точке все потоки ждут, когда другие завершат работу, 
			#pragma omp single //nowait//master//atomic//single nowait//critical  //будет выполняться только одним потоком (мастером). Иначе каждый поток будет увеличивать переменную на 1, проверить в этом случае вывод
			{   //выполняется только одним потоком (первым свободным)
				i++;// все потоки проверяют именно это значение
				printf("in single number_tread=%d i=%d k=%d\n",omp_get_thread_num(),i,k);
			}//неявный барьер single, здесь все доступные потоки обязаны встретиться
		} 
			printf("number_tread=%d i=%d k=%d\n",omp_get_thread_num(),i,k);
	//неявный барьер parallel region
	}
//возможно зависание программы. Причина в том, что один из потоков (А) ни разу не зашел в цикл, т.к. siggle (Б) успел изменить значение i еще до того, как А проверил условие  i<1
//в этом случае А не попал на неявный барьер single, где его ждет Б, в то же время А ждет Б на неявном барьере parallel region
	puts("Ok");
//Как правильно засечь время
	auto start = std::chrono::system_clock::now();
	double r=0;k=11111111;
	#pragma omp parallel for   reduction(+:r)
	for(int i=0; i<k; i++){
		r=r+i;;
	}
	auto end = std::chrono::system_clock::now();
	int elapsed_ms = static_cast<int>(chrono::duration_cast<std::chrono::milliseconds>(end - start).count() );
	printf("ntime=%d sum=%lf\n",elapsed_ms,r);
	start = std::chrono::system_clock::now();
	r=0;
	for(int i=0; i<k; i++){
		r=r+i;;
	}
	end = std::chrono::system_clock::now();
	elapsed_ms = static_cast<int>(chrono::duration_cast<std::chrono::milliseconds>(end - start).count() );
	printf("ntime=%d sum=%lf\n",elapsed_ms,r);
	return 0;

}

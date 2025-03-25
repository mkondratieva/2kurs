#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<iostream>
#include<string.h>
#include<ctime>
using namespace std;
int main(){
       //omp_set_num_threads (1);
	srand(time(NULL));
	#pragma omp parallel for //num_threads(3)
 	for(int i=0; i<10; i++)
   		printf("i=%d number_thread=%d\n",i,omp_get_thread_num());
       //return 0;

	int s=0,k=10000,i;
	for( i=0; i<k; i++){
		s+=i;
	}
	printf("%d =true\n",s);
        s=0; 
	#pragma omp parallel for  
 		for( i=0; i<k; i++){
			s+=i;
	}
	printf("%d =gonka\n",s);

	s=0; int s1=0;
	#pragma omp parallel  sections  private(i) shared(s,s1)
	{  
		#pragma omp    section 
		for(i=0; i<k/2; i++){
			s+=i;
		}
		#pragma omp    section  
        	for(i=k/2; i<k; i++){
			s1+=i;
		}
	}
	printf("%d =sections\n",s+s1);
       //   return 0;
	i=0; 
	#pragma omp parallel  shared(i) 
	{ 
		int  k=0;
		for( ;i<1111;) { // i -- разделяемая (общая) переменная, поэтому каждый поток может ее изменять
		//#pragma omp barrier //барьер -- средство синхронизации между потоками. В этой точке все потоки ждут, когда другие завершат работу, посмотреть и понять, что будет, если убрать здесь барьер
		        k++;
			#pragma omp master  //будет выполняться только одним потоком (мастером). Иначе каждый поток будет увеличивать переменную на 1, проверить в этом случае вывод
				i++;
		} 
		
			printf("k=%d number_tread=%d i=%d\n",k,omp_get_thread_num(),i);
	}
	puts ("done");
	return 0;
}


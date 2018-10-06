#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

int a1[1000000], a2[1000000], size1, size2, *na1, *na2, tmp1=0, tmp2=0;

int cmp(const void *s1, const void *s2)
{
		return *(int *)s1 - *(int *)s2;
}
void Mymerge(int A[], int m, int B[], int n)  
{  
		while (m + n > 0)  
		{  
				if (m > 0 && n > 0)  
				{  
						if (A[m-1] > B[n-1])  
						{  
								A[m - 1 + n] = A[m-1];  
								m = m - 1;  
						}  
						else
						{  
								A[m - 1 + n] = B[n-1];  
								n = n - 1;  
						}  
				}  
				else if (n > 0)
				{  
						A[m - 1 + n] = B[n-1];  
						n = n - 1;  
				}  
				else
				{  
						m = m - 1;  
				}  
		} 
}

void* MyMkrandThread1(void *argu) {

		int i=0;

		for(i=0; i<size1; i++){
				a1[i] = rand();
		}

		qsort(a1, size1, sizeof(int), cmp);

		return ;
}
void* thread1(void*);
void* thread2(void*);
void* thread3(void*);


int main(int argc, char const *argv[])
{
		int rand_seed, i, size, *na1, *na2, a1tmp[1000000], a2tmp[1000000];
		pthread_t mkrand1;
		pthread_t t1;
		pthread_t t2;
		pthread_t t3;

		size = atoi(argv[2]);
		rand_seed = atoi(argv[1]);
		srand(rand_seed);

		if(size%2 == 1){
				size1 = size/2;
				size2 = size/2+1;
		}
		else{
				size1 = size2 = size/2;
		}

		pthread_create(&mkrand1, NULL,  MyMkrandThread1, NULL);
		pthread_create(&t1, NULL, thread1, NULL);

		pthread_join(mkrand1, NULL);
		pthread_join(t1, NULL);

		Merge(a1, size1, a2, size2);

		for(i=0; i<size1; i++){
			a1tmp[i] = a1[i];
		}
		for(i=size1-1; i<size; i++){
			a2tmp[i-size1+1] = a1[i];
		}

		na1 = a1tmp;
		na2 = a2tmp;
		pthread_create(&t2, NULL, thread2, (void*)na1);
		pthread_create(&t3, NULL, thread3, (void*)na2);

		pthread_join(t2, NULL);
		pthread_join(t3, NULL);

		printf("%d\n", tmp1+tmp2);

		return 0;
}


void* thread1(void *argu){

		int i=0;

		for(i=0; i<size2; i++){
				a2[i] = rand();
		}

		qsort(a2, size2, sizeof(int), cmp);

		return ;
}
void* thread2(void *argu){

		int i=0, tmp, *num;
		num = (int *)argu;

		for(i=1; i<size1; i++){
///				printf("num1[%d]=%d", i, num[i]);
				tmp = num[i] - num[i-1];
				tmp1 += tmp;
		}
		return ;
}
void* thread3(void *argu){

		int i=0, tmp, *num;
		num = (int *)argu;

		for(i=1; i<size2+1; i++){
///				printf("num2[%d]=%d", i, num[i]);
				tmp = num[i] - num[i-1];
				tmp2 += tmp;
		}
		return ;
}




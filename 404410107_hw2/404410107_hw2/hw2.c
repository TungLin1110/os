#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#define array_size 1000000

int a1[array_size], a2[array_size], size, size_l, size_r, *temp1, *temp2, total1=0, total2=0;

int cmp(const void *x, const void *y){									//qsort small to big 
	return *(int *)x - *(int *)y;
}
void Mymerge(int A[], int l, int B[], int r){  
	while (l + r > 0)  {  
		if (l > 0 && r > 0){  
			if (A[l-1] > B[r-1]){  
				A[l - 1 + r] = A[l-1];  
				l = l - 1;  
			}  
			else{  
				A[l - 1 + r] = B[r-1];  
				r = r - 1;  
			}  
		}  
		else if (r > 0){  
			A[l - 1 + r] = B[r-1];  
			r = r - 1; 
		}  
		else{  
			l = l - 1;  
		}  
	} 
}

void MyMkrandThread1(void) {
		int i=0;
		for(i=0; i<size_l; i++){
				a1[i] = rand();
		}
		qsort(a1, size_l, sizeof(int), cmp);
		return ;
}
void MyMkrandThread2(void){
		int i=0;
		for(i=0; i<size_r; i++){
				a2[i] = rand();
		}
		qsort(a2, size_r, sizeof(int), cmp);
		return ;
}
void MyAddThread1(void *x){
		int i=0, *arr, tmp;
		arr = (int *)x;
		for(i=1; i<size_l; i++){
				tmp = arr[i] - arr[i-1];
				total1 += tmp;
		}
		return ;
}
void MyAddThread2(void *x){
		int i=0, *arr, tmp;
		arr = (int *)x;
		for(i=1; i<size_r+1; i++){
				tmp = arr[i] - arr[i-1];
				total2 += tmp;
		}
		return ;
}



int main(int argc, char const *argv[])
{
		int rand_seed, i, a1_l[array_size], a1_r[array_size];
		
		rand_seed = atoi(argv[1]);
		srand(rand_seed);
		size = atoi(argv[2]);
		
		//separate the size into size_l and size_r
		if(size%2 == 1){
				size_l = size/2;
				size_r = size/2+1;
		}
		else{
				size_l = size/2;
				size_r = size/2;
		}

		pthread_t mkrand1;
		pthread_t mkrand2;
		//mk rand array by using two threads
		pthread_create(&mkrand1, NULL, (void *)MyMkrandThread1, NULL);
		pthread_create(&mkrand2, NULL, (void *)MyMkrandThread2, NULL);
		pthread_join(mkrand1, NULL);
		pthread_join(mkrand2, NULL);

		Mymerge(a1, size_l, a2, size_r);										//store sorted a1 and a2 into a1

		printf("Array: ");
		for(i=0; i<size; i++){
			printf("%d  ",a1[i]);
		}
		printf("\n");

		for(i=0; i<size_l; i++){
			a1_l[i] = a1[i];
		}
		for(i=size_l-1; i<size; i++){
			a1_r[i-size_l+1] = a1[i];
		}

		temp1 = a1_l;
		temp2 = a1_r;

		pthread_t add1;
		pthread_t add2;
		//add the total of two arrays by using two threads
		pthread_create(&add1, NULL, (void *)MyAddThread1, (void*)temp1);
		pthread_create(&add2, NULL, (void *)MyAddThread2, (void*)temp2);
		pthread_join(add1, NULL);
		pthread_join(add2, NULL);
		//add the final total and print
		printf("%d\n", total1+total2);

		return 0;
}








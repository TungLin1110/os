#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#define size 1024 
#define shm_key 0x11
int main(int argc, char const *argv[])
{
//key_t shm_key;
//printf("input key : ");
//scanf("%d",&shm_key);
struct shmid_ds shmbuffer;

int segment_id= shmget(shm_key, size ,IPC_CREAT|0666); 

shmctl(segment_id, IPC_STAT, &shmbuffer);

	printf("Segment ID : %d\n", segment_id);
	printf("Key : %d\n", shmbuffer.shm_perm.__key);
	//printf("Mode : %d\n", shmbuffer.shm_perm.mode);    
	printf("UID : %d\n", shmbuffer.shm_perm.uid);
	printf("Size : %d\n", shmbuffer.shm_segsz); 
	printf("Attaches : %d\n", shmbuffer.shm_nattch);
	printf("Mode:"); 
	if(shmbuffer.shm_perm.mode&0400)	printf("r");
	else		printf("-");

	if(shmbuffer.shm_perm.mode&0200)	printf("w");
        else            printf("-");
	
	if(shmbuffer.shm_perm.mode&0100)   	printf("a");
        else            printf("-");



	if(shmbuffer.shm_perm.mode&0040) 	  printf("r");
        else            printf("-");
	
	if(shmbuffer.shm_perm.mode&0020)	printf("w");
        else            printf("-");

	if(shmbuffer.shm_perm.mode&0010)  	 printf("a");
        else            printf("-");


	
	if(shmbuffer.shm_perm.mode&0004)  	 printf("r");
        else            printf("-");

        if(shmbuffer.shm_perm.mode&0002) 	  printf("w");
        else            printf("-");

        if(shmbuffer.shm_perm.mode&0001)  	 printf("a");
        else            printf("-");
	return 0;
}

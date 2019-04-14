#define _GNU_SOURCE
#define MAX_BUF 128
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<assert.h>
#include<errno.h>
#include<sched.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/time.h>
#include<fcntl.h>

#define ALLOC_SIZE (100*1024*1024)

//char ftarget[]="test.txt";
//char fname[]="TEST_DOCU/task1_text.txt";

int main(int argc,char *argv[]){
	cpu_set_t set;
	int cpu_num[2]={2,3};
	size_t set_size=4;
	//char buf[MAX_BUF];
	char* test_file=(char*)malloc(ALLOC_SIZE);
	memset(test_file,0x41,ALLOC_SIZE);
	char* test_file2=(char*)malloc(ALLOC_SIZE);
	memset(test_file2,0x01,ALLOC_SIZE);
	//int fd1,fd2,write_size,read_size;
	struct timeval stime,etime,gap;
	gettimeofday(&stime,NULL);
	int pid=getpid();
	for(int i=0;i<2;i++){
		CPU_ZERO(&set);
		CPU_SET(cpu_num[i],&set);
		set_size=sizeof(&set);
		/*if(CPU_ISSET(cpu_num[i],&set)==1)
			printf("\n 2번 프로세스는 현재 %d 번 CPU와 친합니다.\n",cpu_num[i]);*/
		sched_setaffinity(pid,set_size,&set);
		for(int j=0;j<300000000;j++){
			memcpy(test_file2,test_file,sizeof(test_file));
		}
	}
	free(test_file);
	free(test_file2);
	gettimeofday(&etime,NULL);
	gap.tv_sec=etime.tv_sec-stime.tv_sec;
	gap.tv_usec=etime.tv_usec-stime.tv_usec+1000000;
	printf("2번 태스크 수행시간 : %ld sec , %ld usec \n", gap.tv_sec, gap.tv_usec);
}

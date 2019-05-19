#define _GNU_SOURCE
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

#define ALLOC_SIZE (18*1024*1024)

int main(int argc,char *argv[]){
	cpu_set_t set;
	int cpu_num[6]={0,1,2,3,4,5};
	int cpu_number=4;
	size_t set_size=6;
	char* test_file=(char*)malloc(ALLOC_SIZE);
	memset(test_file,0x41,ALLOC_SIZE);
	char* test_file2=(char*)malloc(ALLOC_SIZE);
	memset(test_file2,0x01,ALLOC_SIZE);
	struct timeval stime,etime,gap;
	gettimeofday(&stime,NULL);
	int pid=getpid();
	for(int i=0;i<1000000;i++){
		CPU_ZERO(&set);
		CPU_SET(cpu_num[cpu_number],&set);
		set_size=sizeof(&set);
		cpu_number++;
		if(cpu_number==6)
			cpu_number=4;
		sched_setaffinity(pid,set_size,&set);
		for(int j=0;j<10000;j++){
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

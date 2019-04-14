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

char ftarget[]="test.txt";
char fname[]="TEST_DOCU/task4_text.txt";

int main(int argc,char *argv[]){
	cpu_set_t set;
	//int cpu_num[4]={0,1,2,2};
	size_t set_size=4;
	char buf[MAX_BUF];
	int fd1,fd2,write_size,read_size;
	struct timeval stime,etime,gap;
	gettimeofday(&stime,NULL);
	int pid=getpid();
	CPU_ZERO(&set);
	CPU_SET(3,&set);
	set_size=sizeof(&set);
	sched_setaffinity(pid,set_size,&set);
	// for(int i=0;i<4;i++){
		/*if(CPU_ISSET(cpu_num[i],&set)==1)
			printf("\n 2번 프로세스는 현재 %d 번 CPU와 친합니다.\n",cpu_num[i]);*/
		for(int j=0;j<20;j++){
			fd1=open(ftarget,O_RDONLY);
			fd2=open(fname,O_WRONLY | O_CREAT | O_TRUNC,0664);
			while(1){
				read_size=read(fd1,buf,MAX_BUF);
					if(read_size==0)
						break;
				write_size=write(fd2,buf,read_size);	
			}
			close(fd1);
			close(fd2);
		}
	//}
	gettimeofday(&etime,NULL);
	gap.tv_sec=etime.tv_sec-stime.tv_sec;
	gap.tv_usec=etime.tv_usec-stime.tv_usec+1000000;
	printf("4번 태스크 수행시간 : %ld sec , %ld usec \n", gap.tv_sec, gap.tv_usec);
}

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <signal.h>

#define FILE_PATH "/dev/ttyUSB0"


int main(int argc,char *argv[])
{
	return main_signal();

}

//extern int open (const char *__file, int __oflag, ...)

void sa_handle(int signo)
{
	printf("signo : %d\n",signo);
}


int main_signal()
{
	struct sigation act;
	struct sigation old_act;

	act.sa_handler = sa_handler;

	sigempty(act.sa_mask);
	act.sa_flag = 0;
	sigaction(SIGIO,&act,&old_act);
	
	pid_t pid;
	pid = fork();


	if(pid == 0){
		while(1){
			printf("i am child\n");
			sleep(1);
		}
		reutrn 0;
	}

	while(1){
		static int count = 0;
		count++;

		if(count >= 3){
			sigaction(SIGIO,&old_act,NULL);
			kill(pid,SIGKILL);
		}
		printf("i am father\n");
		sleep(1);
	}

	return 0;
}

int main_noblock(void)		//block and noblock
{

	char  buf[64] = {0};
	// if file is created use the mode S_IRWXU ...
	//default block
	int fd = open(FILE_PATH,O_RDWR | O_NONBLOCK);

	if(fd <= 0){
		perror(strerror(errno));
		return -1;
	}
	ssize_t ret = read(fd,buf,sizeof(buf));
	close(fd);	
	return 0;
}



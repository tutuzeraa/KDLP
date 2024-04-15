#include<stdio.h>
#include<unistd.h>
#include<errno.h>

int BUF_SIZE = 256;

int main(int argc, char **argv)
{
	char buf[BUF_SIZE];
	char *cur_dir = getcwd(buf, BUF_SIZE);
	
	printf("%s$ \n", cur_dir);

	return 0;
}	


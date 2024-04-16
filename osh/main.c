#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>

int BUF_SIZE = 256;

int main(int argc, char **argv)
{
	char buf[BUF_SIZE];
	char user_input[BUF_SIZE];
	char *cur_dir;	

	while (1) {
		cur_dir = getcwd(buf, BUF_SIZE);
		printf("%s$ \n", cur_dir);

		if (fgets(user_input, BUF_SIZE, stdin) == NULL) break;

		if (!strcmp(user_input, "\n")) continue;
		
		printf("Unrecognized command\n");
	}

	return 0;
}	


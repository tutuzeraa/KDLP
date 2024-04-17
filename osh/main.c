#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<unistd.h>
#include<errno.h>

int BUF_SIZE = 256;

char** splitCmd(char *user_input, char **cmd){
	int j = 0;
	char *c;
	char word[256] = {0}; //fix this

	for(int i = 0; i < BUF_SIZE; i++){
		c = &user_input[i]; 
		printf("c: %s\n", c);
		if(*c == '\0' || *c == '\n'){ 
			cmd[j] = strndup(word, BUF_SIZE); 
			break;
		} else if(isspace(*c)){
			cmd[j] = strndup(word, BUF_SIZE); 
			memset(word, 0, 256);
			j++;
		}	
		strncat(word, c, 1);
	}

	return cmd;
}

int main(int argc, char **argv)
{
	char buf[BUF_SIZE];
	char user_input[BUF_SIZE];
	char *cur_dir;	
	char **cmd = malloc(BUF_SIZE * sizeof(char*)); 

	while (1) {
		cur_dir = getcwd(buf, BUF_SIZE);
		printf("%s$ \n", cur_dir);

		if (fgets(user_input, BUF_SIZE, stdin) == NULL) break;

		if (!strcmp(user_input, "\n")) continue;

		cmd = splitCmd(user_input, cmd);

		printf("Unrecognized command %s\n", cmd[0]);
	}

	return 0;
}	


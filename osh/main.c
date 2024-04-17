#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<unistd.h>
#include<errno.h>

#define BUF_SIZE 256
const int num_builtins = 3; 


int osh_cd(char **args);
int osh_exec(char**args);
int osh_exit(char **args);

char *builtin_cmd[] = {
  "cd",
  "exec",
  "exit",
};

int (*builtin_func[]) (char **) = {
  &osh_cd,
  &osh_exec,
  &osh_exit,
};


char** splitCmd(char *user_input)
{
	int j = 0;
	char *c;
	char word[BUF_SIZE] = {0};
  char **cmd = malloc(BUF_SIZE * sizeof(char*));

	for(int i = 0; i < BUF_SIZE; i++){
		c = &user_input[i]; 
		if(*c == '\0' || *c == '\n'){ 
			cmd[j] = strndup(word, BUF_SIZE); 
			break;
		} else if(isspace(*c)){
			cmd[j] = strndup(word, BUF_SIZE); 
			memset(word, 0, 256);
			j++;
		}	else{
		  strncat(word, c, 1);
    }
	}
  // cmd[j] = NULL;

	return cmd;
}

int osh_cd(char **args)
{
  char *usage_info = "cd receives only 1 argument, the destination directory\n";

  if(args[2] != NULL)
    fprintf(stderr, "%s", usage_info);
  else
    if(chdir(args[1]) != 0)
      perror("cd didn`t work!\n");
    
  return 1;
}

int osh_exit(char **args)
{
  if(args[2] != NULL){
    fprintf(stderr, "exit does not receive arguments!\n");
    return 1;
  }  

  return 0;
}

int osh_exec(char **args){
  
  if(args[1] == NULL){
    fprintf(stderr, "exec need at least 1 argument\n");
    return 1;
  }
  
  int i = 0;
  char **exec_args = malloc(BUF_SIZE * sizeof(char*));
  while (args[i+2] != NULL){
    exec_args[i] = strndup(args[2+i], BUF_SIZE);
    printf("arg %d: %s\n", i, exec_args[i]);
    i++;
  }
  
  if(execv(args[1], exec_args) != 0)
    perror("exec didn`t work!\n");
  
  free(exec_args);
  return 1;
}

int execute(char **cmd)
{
  for(int i = 0; i < num_builtins; i++){
    // printf("cmd %s, builtin %s\n", cmd[0], builtin_cmd[i]);
    if(strcmp(cmd[0], builtin_cmd[i]) == 0){
      return (*builtin_func[i])(cmd);
    }
  }

	printf("Unrecognized command %s\n", cmd[0]);
  return 1;
}

int main(int argc, char **argv)
{
	char buf[BUF_SIZE];
	char user_input[BUF_SIZE];
	char *cur_dir;	
	char **cmd; 
  int status = 1;

	do {
		cur_dir = getcwd(buf, BUF_SIZE);
		printf("%s$ \n", cur_dir);

		if (fgets(user_input, BUF_SIZE, stdin) == NULL) break;

		if (!strcmp(user_input, "\n")) continue;

		cmd = splitCmd(user_input);

    status = execute(cmd);

    free(cmd);
	} while(status);

	return 0;
}	


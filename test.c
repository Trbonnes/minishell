#include "includes/fonction.h"

int main(int ac, char **av, char **env)
{

	execve("/bin/cat", av, env);
	// printf("av = %s\n", av[1]);
	return (0); 
}
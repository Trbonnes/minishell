#include "includes/fonction.h"

int main(int ac, char **av, char **env)
{
	execve("/bin/cat", av, env);
	return (0); 
}
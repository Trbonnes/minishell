# 42 Cursus Minishell

Extract from the Project Subject :

" The objective of this project is for you to create a simple shell. Yes, your
little bash or zsh. You will learn a lot about processes and file descriptors. "

---

My Minishell
===============

### Overview
This project is written in C. This is a group of project done with onr other 42 students.
It's a minimal version of a shell taking bash as a reference (https://www.gnu.org/savannah-checkouts/gnu/bash/manual/) handling :
- echo cd pwd export unset env exit as built-in
- executables files and commands with execve and PATH
- ' and "
- environment variables
- < > << >> redirections
- pipes
- signals (ctrl-C ctrl-D ctrl-\)

To be honest this project is a bit messy and you can find way better Minishells on github.

### Test
This project is designed to work on MacOs
To test it simply run make aned launch minishell. You can now use it like bash (a really trimed down version of bash).

### Contact
trbonnes@student.42.fr
trdella-@student.42.fr

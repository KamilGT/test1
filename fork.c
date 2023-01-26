#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h>

int main()
{
    pid_t pid; // идентификатор процесса
    printf("PARENT process, my PID is %d\n", getpid());

    pid = fork(); // создаем дочерний процесс
    if (pid == 0) // Если это дочерний процесс, то для него pid=0  
    { 
        printf("Child process. My PID is %d\n", getpid());
        sleep(2); // при втором запуске попробовать поменять здесь на 5, а ниже sleep на 2
        printf("CHILD is finished\n"); 
    }
    if (pid < 0) // если процесс не создался pid < 0
        printf("Can't create process: error %d\n", pid);
    sleep(5);// здесь помнять на 2, тогда родительский процесс завершится быстрее чем дочерний
    printf("PARENT is finished\n");

    //wait(pid);
    return 0;
}

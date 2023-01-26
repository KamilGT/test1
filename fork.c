#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    pid_t pid; // идентификатор процесса
    printf("PARENT process BEGIN, my PID is %d\n", getpid());

    pid = fork(); // создаем дочерний процесс
    if (pid < 0) // если процесс не создался pid < 0
    {
        printf("Can't create process: error %d\n", pid);
        exit(1); // выход из программы с кодом 1, exit - системный выход 
    }
    if (pid == 0) // Если это дочерний процесс, то для него pid=0  
    { 
        printf("Child process. My PID is %d\n", getpid());
        sleep(2); //Даем время родительском процессу заверщиться точно раньше, если ниже не буде wait, то программа закончиться? а дочерний процесс не успеет завершиться 
        printf("CHILD is finished\n"); 
    }
    else
    {
        sleep(5); // Для того, чтобы дочерний завершился раньше/ Для проверки, что будет в этом случае, при это wait должен быть включен
        printf("Its's PARENT process here, my PID is %d\n", getpid());
        wait(NULL);  // ожидание завершение дочернего процесса, только потом завершается материнский
        printf("PARENT is finished\n");
    }

    return 0;
}

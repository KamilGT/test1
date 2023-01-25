#include <stdio.h>
#include <malloc.h> /* для определения ptrdiff_t в GLIBC */
#include <unistd.h>
#include <alloca.h> /* лишь для демонстрации */
#include <stdlib.h>

extern void afunc(void); /* функция, показывающая рост стека */

int bss_var; /* автоматически инициализируется в 0, должна быть в сегменте BSS */
int data_var = 42; /* инициализируется в не 0, должна быть в сегменте данных */
int main(int argc, char **argv) /* аргументы не используются */
{
    char *p, *b, *nb, *str;
    long unsigned int i;
    system("clear");

    str = (char*)alloca(100); //выделяем место на стеке (100 символов) для переменной str 

    printf("Text Locations (CODE Segments):\n");

    printf("\tAddress of main: %p   ", main);
    sprintf(str, "%p", main); //преобразовываем 16-ый адрес в строку (массив символов)
    sscanf(str, "%lx", &i); //преобразовываем строку (массив символов) в long unsigned int 
    printf("В байтах= %lu\n",  i); //выводим на экран значение в байтах

    printf("\tAddress of afunc: %p   ", afunc);
    sprintf(str, "%p", afunc);
    sscanf(str, "%lx", &i);
    printf("В байтах= %lu\n",  i);


    printf("Stack Locations:\n");
    afunc();

    p = (char*)alloca(10); //выделяем место на стеке (10 символов) для переменной p
//p = (char*)malloc(10);  //Если использовать эту функцию вместо alloca() место выделится в куче (нужен free)
    printf("\nВыделяем в СТЕКЕ место для элементов массива p[] при помощи функции alloca():\n");
    if (p != NULL) {
        printf("\t 1 elem. of alloca()'ed array: %p\n", &*p); //адрес начала строки (массив символов)
        printf("\tStart    of alloca()'ed array: %p   ", &p[0]); // адрес первого символа (такой же)
        sprintf(str, "%p", &p[0]);
        sscanf(str, "%lx", &i);
        printf("В байтах= %lu\n",  i);

        printf("\t 2 elem. of alloca()'ed array: %p   ", &p[1]); // адрес второго символа
        sprintf(str, "%p", &p[1]);
        sscanf(str, "%lx", &i);
        printf("В байтах= %lu\n",  i);

        printf("\tEnd      of alloca()'ed array: %p   ", &p[12]); // адрес тринадцатого символа
        sprintf(str, "%p", &p[12]);
        sscanf(str, "%lx", &i);
        printf("В байтах= %lu\n",  i);
    }

    printf("\nData Locations:\n");
    printf("\tAddress of data_var (инициализированная): %p   ", &data_var); //адрес переменной data_var
    sprintf(str, "%p", &data_var);
    sscanf(str, "%lx", &i);
    printf("В байтах= %lu\n",  i);

    printf("BSS Locations:\n");
    printf("\tAddress of bss_var (неинициализированная): %p   ", &bss_var); // адрес переменной bss_var
    sprintf(str, "%p", &bss_var);
    sscanf(str, "%lx", &i);
    printf("В байтах= %lu\n",  i);


    b = sbrk((ptrdiff_t)64); /* увеличить адресное пространство для сегмента данных (за счет кучи)  */
    nb = sbrk((ptrdiff_t)0); //определяем, где в настоящее время заканчивается адресное пространство
    printf("\nHeap Locations:\n");
    printf("\tInitial end of heap: %p   ", b);
    sprintf(str, "%p", b);
    sscanf(str, "%lx", &i);
    printf("В байтах= %lu\n",  i);

    printf("\tSecond end of heap:  %p   ", nb); //демонстрируем, где заканчивается адресное пространство после прироста
    sprintf(str, "%p", nb);
    sscanf(str, "%lx", &i);
    printf("В байтах= %lu\n",  i);

    b = sbrk((ptrdiff_t)-16); /* сократить его */
    nb = sbrk((ptrdiff_t)0); // показать конец адресного пространства
    printf("\tThird end of heap: %p   ", b);
    sprintf(str, "%p", b);
    sscanf(str, "%lx", &i);
    printf("В байтах= %lu\n",  i);

    printf("\tFinal end of heap: %p   ", nb); //демонстрируем, где заканчивается адресное пространство после уменьшения
    sprintf(str, "%p", nb);
    sscanf(str, "%lx", &i);
    printf("В байтах= %lu\n",  i);
}

void afunc(void)
{
    char str[100]; //выделяем место (100 символов) для переменной str (думаю что на стеке, другим способом)
    long unsigned int i; //локальная переменная - в стеке
    static int level = 0; /* статическая переменная, инициализируется */
    auto int stack_var; /* объявлена АВТОМАТИЧЕСКАЯ переменная, чтобы она точно была в стеке */

    if (++level == 6) /* избежать бесконечной рекурсии */
    return;

    printf("\tStack level     %d:  %p  address of stack_var (автомат.): %p   ", level, &level, &stack_var);
    //адреса переменных level и stack_var
    sprintf(str, "%p", &level);
    sscanf(str, "%lx", &i);
    printf("В байтах= %lu   ",  i);
    sprintf(str, "%p", &stack_var);
    sscanf(str, "%lx", &i);
    printf("В байтах= %lu\n",  i);

    stack_var = 10000;
    printf("\tStack level NEW %d:  %p  address of stack_var (автомат.): %p   ", level, &level, &stack_var);
    //адреса переменных level и stack_var после присвоения stack_var нового значения
    sprintf(str, "%p", &level);
    sscanf(str, "%lx", &i);
    printf("В байтах= %lu   ",  i);
    sprintf(str, "%p", &stack_var);
    sscanf(str, "%lx", &i);
    printf("В байтах= %lu\n",  i);

    afunc(); /* рекурсивный вызов, чтобы продемонстрировать резервирование переменных на новых адресах в стеке */
}

// Мой код
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    int opt;
    
    // если программа запущена без аргументов просто ./program
    if (argc == 1){
        printf("Использование: %s [опции]\n", argv[0]);
        printf("Опции:\n");
        printf("  -i  Показать ID пользователя и группы\n");
        return 0;
    }
    
    while ((opt = getopt(argc, argv, "i")) != -1){
        if (opt == 'i'){ //опция -i
            printf("Реальный ID пользователя: %d\n", getuid());
            printf("Эффективный ID пользователя: %d\n", geteuid());
            printf("Реальный ID группы: %d\n", getgid());
            printf("Эффективный ID группы: %d\n", getegid());
        }
        else if (opt == '?'){
            //Неизвестная опция ошбика
            printf("Неизвестная опция: %c\n", opt);
        }
    }
    return 0;
}
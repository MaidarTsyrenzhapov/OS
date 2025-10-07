#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]){
    int opt;
    
    if (argc == 1){
        printf("Использование: %s [опции]\n", argv[0]);
        printf("Опции:\n");
        printf("  -i  Показать ID пользователя и группы\n");
        printf("  -p  Показать идентификаторы процесса\n");
        printf("  -s  Стать лидером группы процессов\n");
        printf("  -u  Показать значение ulimit\n");
        printf("  -c  Показать размер core-файла\n");
        printf("  -d  Показать текущую директорию\n");
        printf("  -v  Показать переменные среды\n");
        return 0;
    }
    
    while ((opt = getopt(argc, argv, "ispucdv")) != -1){
        switch(opt){
            case 'i':
                printf("=== Идентификаторы пользователя и группы ===\n");
                printf("Реальный ID пользователя: %d\n", getuid());
                printf("Эффективный ID пользователя: %d\n", geteuid());
                printf("Реальный ID группы: %d\n", getgid());
                printf("Эффективный ID группы: %d\n", getegid());
                break;
            case 's':
                printf("=== Становление лидером группы ===\n");
                if (setpgid(0, 0) == 0) {
                    printf("Стал лидером группы процессов. Новый PGID: %d\n", getpgrp());
                } else {
                    perror("Ошибка при установке лидера группы");
                }
                break;
            case 'p':
                printf("=== Идентификаторы процесса ===\n");
                printf("ID процесса: %d\n", getpid());
                printf("ID родительского процесса: %d\n", getppid());
                printf("ID группы процессов: %d\n", getpgrp());
                break;
            case 'u':
                printf("=== Ulimit ===\n");
                struct rlimit rlim;
                if (getrlimit(RLIMIT_FSIZE, &rlim) == 0) {
                    printf("Текущий ulimit: %ld\n", (long)rlim.rlim_cur);
                } else {
                    perror("Ошибка при получении ulimit");
                }
                break;
            case 'c':
                printf("=== Размер core-файла ===\n");
                struct rlimit core_lim;
                if (getrlimit(RLIMIT_CORE, &core_lim) == 0) {
                    printf("Максимальный размер core-файла: %ld байт\n", (long)core_lim.rlim_cur);
                } else {
                    perror("Ошибка при получении размера core-файла");
                }
                break;
            case 'd':
                printf("=== Текущая директория ===\n");
                char cwd[1024];
                if (getcwd(cwd, sizeof(cwd)) != NULL) {
                    printf("Текущая директория: %s\n", cwd);
                } else {
                    perror("Ошибка при получении текущей директории");
                }
                break;
            case 'v':
                printf("=== Переменные среды ===\n");
                extern char **environ;
                for (char **env = environ; *env != NULL; env++) {
                    printf("%s\n", *env);
                }
                break;
            case '?':
                printf("Неизвестная опция: %c\n", optopt);
                break;
        }
    }
    return 0;
}

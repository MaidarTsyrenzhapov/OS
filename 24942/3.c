#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    printf("=== Шаг 1: Исходные идентификаторы ===\n");
    printf("Реальный ID пользователя: %d\n", getuid());
    printf("Эффективный ID пользователя: %d\n", geteuid());
    
    printf("\n=== Попытка открыть файл ===\n");
    FILE *file = fopen("secret.txt", "r");
    if (file == NULL) {
        perror("Ошибка при открытии файла");
    } else {
        printf("Файл успешно открыт\n");
        fclose(file);
    }
    
    printf("\n=== Устанавливаем эффективный ID равным реальному ===\n");
    if (setuid(getuid()) == -1) {
        perror("Ошибка при setuid");
    } else {
        printf("Реальный и эффективный ID теперь совпадают\n");
    }
    
    printf("\n=== Шаг 2: Идентификаторы после setuid ===\n");
    printf("Реальный ID пользователя: %d\n", getuid());
    printf("Эффективный ID пользователя: %d\n", geteuid());
    
    printf("\n=== Повторная попытка открыть файл ===\n");
    file = fopen("secret.txt", "r");
    if (file == NULL) {
        perror("Ошибка при открытии файла");
    } else {
        printf("Файл успешно открыт\n");
        fclose(file);
    }
    
    return 0;
}
// Последнее обновление: Ср 08 окт 2025 17:36:52 +07

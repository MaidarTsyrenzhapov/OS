#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main() {
    time_t t = time(NULL);
    
    printf("UTC время: %s", asctime(gmtime(&t)));
    printf("Локальное время: %s", ctime(&t));
    
    setenv("TZ", "PST8PDT", 1);
    tzset();
    printf("Калифорния (PST/PDT): %s", ctime(&t));
    
    return 0;
}
// Последнее обновление: Ср 08 окт 2025 17:36:52 +07

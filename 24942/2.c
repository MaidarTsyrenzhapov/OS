#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main() {
    time_t t = time(NULL); //время в секундах с 01.01.1970
    
    printf("UTC время: %s", asctime(gmtime(&t)));//преобр в tm UTC а потом в читаеую строку
    printf("Локальное время: %s", ctime(&t)); //локальное время
    
    setenv("TZ", "PST8PDT", 1); //-8 время от UTC(PST) а потом в PDT это +1 от PST
    tzset(); //без него не работает
    printf("Калифорния (PST/PDT): %s", ctime(&t));//вывод
    
    return 0;
}

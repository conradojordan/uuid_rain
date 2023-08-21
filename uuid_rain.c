#include <uuid/uuid.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void uuid2binstring(uuid_t uuid, char* out) {
    for (int i=0; i<16; i++) {
        for (int j=0; j<8; j++){
            out[(i*8)+7-j] = (uuid[i]&0x01)+48;
            uuid[i] >>= 1;
        }
    }
}

int aggregate(char* uuid, char* result) {
    int diff = 0;
    for (int i=0; i<128; i++) {
        if (result[i] != uuid[i] && result[i] != 32) {
           result[i] = 32; 
           diff = 1;
        }
    }
    return diff;
}

int main (int argc, char *argv[]) {
    int sleep_period = 200;
    if (argc >= 2) {
        int status;
        status = sscanf(argv[1], "%d", &sleep_period);
        if (status != 1){
            return 1;
        }
    }
    uuid_t uuid;
    uuid_generate(uuid);

    char uuid_str[129];
    char result[129];
    int counter, diff, sleep_time;

    while (1) {
        uuid_generate(uuid);
        uuid2binstring(uuid, uuid_str);
        strcpy(result, uuid_str);
        counter = 0;
        
        while (counter <= 2) {
            printf("%s\n", result);
            uuid_generate(uuid);
            uuid2binstring(uuid, uuid_str);
            diff = aggregate(uuid_str, result);
            if (diff == 0) {
                counter++;
            } else {
                counter = 0;
            }
            usleep(sleep_period*1000);
        }
    }

    return 0;
}

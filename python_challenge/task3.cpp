#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace std;

int main() {

    int fd = open("text.txt", O_RDONLY);

    for(int i = 0; i < 1251; i++) {
        char str[80];
        read(fd, &str, 80);
        for(int j = 4; j < 75; j++)
            if(islower(str[j-4]) && isupper(str[j-3]) && isupper(str[j-2]) && isupper(str[j-1]) &&
                islower(str[j]) && isupper(str[j+1]) && isupper(str[j+2]) && isupper(str[j+3]) && islower(str[j+4])) {
                cout << str[j];
        }
        char c;
        read(fd, &c, 1);
    }
    return 0;
}

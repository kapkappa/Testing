#include <iostream>

using namespace std;

int ENTER = 0;

class Parser {
private:
    enum state {S, B, C, F, ER};
    state CS;
    char c;
    char*buf;
    int index;
public:
    Parser(char*mas) { buf = mas;}
    Parser() {}

    void feed() {
        if(!ENTER) {
            c = getchar();
            if (c == '\n' || c == 0 || c == -1) c = 0;
        } else {
            if (buf != nullptr && buf[index] != 0) {
                c = buf[index++];
            } else
                c = 0;
        }
    }

    bool is_allowed(void) {
        index = 0;
        CS = S;
        do {
            feed();
            switch (CS) {
                case S: if (c == 'a') CS = B;
                        else CS = ER;
                        break;
                case B: if (c == 'b') CS = S;
                        else if (c == 'c') CS = B;
                        else if (c == 'a') CS = C;
                        else CS = ER;
                        break;
                case C: if (c == 'b') CS = C;
                        else if (c == 0) CS = F;
                        else CS = ER;
                        break;
            }
        } while (CS != F && CS != ER);
        if (CS == F) cout<<"YES\n";
        else cout<<"NO\n";
        return 0;
    }

};

int main(int argc, char**argv) {
    if(argc > 1) ENTER = 1;
    Parser A(argv[1]);
    A.is_allowed();
    return 0;
}

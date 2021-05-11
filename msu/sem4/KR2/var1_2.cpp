#include <iostream>

using namespace std;

class Parser {
private:
    char c;

public:
    char get_c() const {
        return c;
    }

    void get_char() {
        c = getchar();
        if (c == '\n' || c == 0 || c == -1) c = 0;
    }

    void S() {
        F();
        while(c=='-' || c=='+') {
            A();
            F();
        }
    }

    void F() {
        if (c == '-') {
            get_char();
            F();
        } else if (c == '(') {
                get_char();
                S();
                if (c == ')') {
                    get_char();
                } else
                    throw c;
        } else I();
    }

    void A() {
        if (c == '+' || c =='-') get_char();
        else throw c;
    }

    void I() {
        D();
        while ((0 <= c-'0') && (c-'0' < 10)) D();
    }

    void D() {
        if ((0 <= c-'0') && (c-'0' < 10)) get_char();
        else throw c;
    }
};

int main (int argc, char**argv) {
    Parser A;
try {
        A.get_char();
        A.S();
        if (!A.get_c()) cout << "YES\n";
        else throw A.get_c();
    } catch (char c) {
        cout << "NO\n";
    }
    return 0;
}

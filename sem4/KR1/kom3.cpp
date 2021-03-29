#include <iostream>

using namespace std;

class A {
private:
    static int f_calls;
public:
    static int f();
    int get() {return f_calls;}
};

int A::f_calls = -1;
int A::f() {
    A::f_calls++;
    A a;
    return a.get();
}

class Functor {
public:
    int operator() (const int& x,const int& y) {
        return x+y;
    }
};

class Smart {
public:
    class help {
    public:
        int elem;
        help(int x) {
            elem = x;
        }
        operator int() const {
            return elem;
        }
        int operator[] (int x) const {
            return (elem-1) * x;
        }
    };
//    friend class help;
    help operator[] (int x) const {
        help tmp(x+1);
        return tmp;
    }
};

class IntStack {
private:
    struct Item {
        int elem;
        Item* next;
    };
    Item* first;
public:
    IntStack() : first(nullptr) {}
    void delet() {
        Item* tmp;
        while(first) {
            tmp = first->next;
            free(first);
            first = tmp;
        }
    }

    Item* insert(Item* list, int elem) {
        if(list==nullptr) {
            list = (Item*)malloc(sizeof(Item));
            list->next = nullptr;
            list->elem = elem;
            return list;
        }
        list->next = insert(list->next, elem);
        return list;
    }

    IntStack operator<< (int elem) {
        cout << elem << endl;
        Item* new_elem = (Item*)malloc(sizeof(Item));
        new_elem->elem = elem;
        new_elem->next = nullptr;
        if (first == nullptr) first = new_elem;
        else {
            Item* pr = first;
            Item* tmp = first->next;
            while(tmp) {
                pr = tmp;
                tmp = tmp->next;
            }
            pr->next = new_elem;
        }
        return *this;
    }

    void print() {
        cout << "PRINT: ";
        Item* tmp = first;
        while(tmp) {
            cout << tmp->elem << " ";
            tmp = tmp->next;
        }
        cout << endl;
    }
//    IntStack operator>>
};


int main() {
// 1
    cout << A::f() << " " << A::f() << endl;

// 2
    Functor b;
    int y = -1;
    cout << b(3, y) << endl;

// 3
    cout << "Bad condition" << endl;

// 4
    Smart c;
    Smart const c2;
    int t1 = c[2], t2=c2[3], t3 = c[2][2], t4 = c2[t1][t2];
    cout << t1 << " " << t2 << " " << t3 << " " << t4 << endl;
    const Smart s;
    cout << s[1] << endl;

// 5
    IntStack i;
    i<<25;
    i<<36;
    i<<49;
    i.print();
    i.delet();
    return 0;
}

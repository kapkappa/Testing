#include <iostream>

using namespace std;

void set_min (int &x,int &y) {
    int tmp = std::min(x,y);
    y = x = tmp;
}

class Flag {
private:
    bool set;
public:
    Flag() : set(false) {}
    void SetOn() { set = true; }
    void SetOff() { set = false; }
    bool IsOn() const { return set; }
    operator bool() const {
        bool res = IsOn();
        return res;
    }
};

class Counted {
public:
    static int elems;
    Counted() { elems++; }
    Counted(const Counted& c) { elems++; }
    ~Counted() {elems--;}
};

class Watched {
public:
    Watched(){}
    static int Amount () {
        return Counted::elems;
    }
};

int Counted::elems = 0;

class A;
class B;

class A {
public:
    int operator[] (const B& b) const {
        return 75;
    }
    int operator() () const {
        return 50;
    }
    int operator() (const B& b) const {
        return 100;
    }
    int operator() (const B& b1, const B& b2) const {
        return 150;
    }
    int operator() (const A& a1, const A& a2, const A& a3) const {
        throw A();
        return 0;
    }
    int operator-- () const {
        return 500;
    }
    int operator-- (int) const {
        return 501;
    }
};

class B {
public:
    int operator[] (const A& a) const {
        return 75;
    }
    int operator() (const A& a) const {
        return 200;
    }
};


class D_f {
public:
    int f;
};

class D {
private:
    D_f sub_class;
public:
    int f;
    D* operator-> () {
        return this;
    }
};

class QueueEmpty {
public:
    QueueEmpty(){ cout << "Queue is empty!" << endl; }
};

class IntQueue {
private:
    int *start, *end;
    int size;
public:
    IntQueue() : start(nullptr), end(nullptr), size(0) {}
    void operator<<= (const int elem) {
        if(Check(elem)) {
            size++;
            start = (int*)realloc(start, size * sizeof(int));
            end = start + size - 1;
            *end = elem;
        }
    }
    int operator>>= (int i) {
        if(!size) throw QueueEmpty();
        int tmp = *start;
        size--;
        int* new_start = (int*)malloc(sizeof(int) * size);
        for(int i = 0; i < size; i++)
            *(new_start+i) = *(start+i+1);
        free(start);
        start = new_start;
        end = start + size - 1;
        return tmp;
    }
    int Amount () const { return size; }
    ~IntQueue() {
        if(start) free(start);
    }
    void print() const {
        for(int i = 0; i < size; i++)
            cout << *(start+i);
        cout << endl;
    }
    virtual bool Check(int elem) {
        return true;
    }
};

class EvenFilter : public IntQueue {
    virtual bool Check(int elem) {
        return !(elem % 2);
    }
};

int main() {
// 1
    int a1(1), a2(2);
    set_min(a1, a2);
    cout << a1 << " " << a2 << endl;

//2+3
    Flag f;
    cout << f.IsOn() << endl;
    f.SetOn();
    cout << f.IsOn() << endl;
    int const c = f.IsOn();
    cout << c << endl;
    if (f) cout << f << endl;
    Flag const f2;
    if (!f2) cout << f2 << endl;

//4
    cout << "Counted: " << Watched::Amount() << endl;
    Counted d1, d2, d3(d1), d4;
    cout << "Counted: " << Watched::Amount() << endl;

//5
    A a5;
    B b5;
    cout << a5[b5] << " " << b5[a5] << endl;
    cout << a5() << " " << a5(b5) << " " << a5(b5, b5) << " " << b5(a5) << endl;
    try {
        cout << a5(a5, a5, a5) << endl;
    }
    catch(A a6) {
        cout << "exeption\n";
    }
    cout << --a5 << " " << a5-- << endl;

//6
    D d;
    d->f = 6;
    cout << d->f << endl;

//7
    IntQueue q;
    q <<= 2;
    q <<= 3;
    q <<= 4;
    q.print();
    int size = q.Amount();
    cout << "Size = " << size << endl;
    for(int i = 0; i < size; i++)
        cout << (q >>= i) << endl;

//8
    EvenFilter eq;
    eq <<= 2;
    eq <<= 3;
    eq <<= 4;
    eq.print();
    return 0;
}

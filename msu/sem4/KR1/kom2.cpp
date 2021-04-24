#include <iostream>

using namespace std;

class Assign {
private:
    int last;
public:
    Assign() : last(0) {}
    void f(int& x, int& y) {
        x = y;
        last = x;
    }
    int Get() const {
        return last;
    }
    Assign* operator-> () {
        return this;
    }
};

class Assign2 {
public:
    template <class T>
    void f(T& x, int& y) {
        x = y;
    }
    Assign2* operator-> () {
        return this;
    }
};

//FIXME
class M {
private:
    static int uniq;
    int elem, number;
public:
    int get() const {
        return number;
    }
    M() : elem(0), number(uniq) {
        uniq++;
    }
    M& operator() (M x) {
        if(number == x.get()) return *this;
        cout << "x != this" << endl;
        return *this;
    }
    int operator= (int e) {
        return elem = e;
    }
    operator int() {
        return elem;
    }
};

int M::uniq = 0;

class SumHold {
private:
    static int SumAll;
    int cor_sum, req_sum;
public:
    SumHold() : cor_sum(0), req_sum(0) {}
    friend SumHold& operator<< (SumHold&, int);
    int get() const { return cor_sum; }
    int getreject() const { return req_sum; }
    void add(int a) {
        if(Acceptable(a))
            cor_sum += a;
        else
            req_sum += a;
        SumAll += a;
    }
    int getall() { return SumAll; }
    static int GetAll();
    virtual bool Acceptable(int a) const { return true; }
};

int SumHold::SumAll = 0;
int SumHold::GetAll() {
    SumHold a;
    return a.getall();
}

SumHold& operator<< (SumHold& s, int a) {
    s.add(a);
    return s;
}

class SumHoldSmall : public SumHold {
public:
    bool Acceptable(int a) const {
        return (a >= -10 && a <= 10);
    }
};

int main() {
// 1
    int x = 4, y = 1;
    Assign a;
    a->f(x,y);
    cout << a.Get() << endl;

// 2
    Assign2 a2;
    double x2 = 0;
    int y2 = 2;
    a2->f(x2,y2);
    cout << x2 << endl;

// 3
    M m, m2;
    m(m) = 3;
    cout << m(m) << endl;
    m(m2) = 3;
    cout << m(m2) << endl;

// 4
    SumHold sh;
    sh<<20<<30<<40<<50;
    cout << sh.get() << endl;

// 5
    SumHold sh2;
    sh2<<0<<12<<-12<<60;
    cout << SumHold::GetAll() << endl;

// 6
    SumHoldSmall sh6;
    sh6 << 10 << 12 << -15 << 3 << 4;
    cout << SumHold::GetAll() << endl;
    cout << SumHoldSmall::GetAll() << endl;
    cout << sh6.get() << endl;
    cout << sh6.getreject() << endl;

    return 0;
}

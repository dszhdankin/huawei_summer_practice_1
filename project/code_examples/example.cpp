//#include <iostream>
class A{
private:
    int a;
    int b;

public:
    A(int a, int b) {
        this->a = a;
        this->b = b;
    }

    void setA(int a) { this->a = a; }
    void setB(int b) { this->b = b; }

    int getA() { return a; }
    int getB() { return b; }
};

struct B {
    char h;
    int a, b, c;
    long long k;
};

int main() {
    /*std::cout << sizeof (B) << std::endl;

    B record;

    long long y = reinterpret_cast<long long>(&record.h);
    std::cout << y << std::endl;
    std::cout << reinterpret_cast<long long>(&record.a) << " " << reinterpret_cast<long long>(&record.b) << " " << reinterpret_cast<long long>(&record.c) << std::endl;
    std::cout << reinterpret_cast<long long>(&record.k) << std::endl;

    A inst(1, 2);

    while (inst.getB()) {
        inst.setA(inst.getA() + 1);
        inst.setB(inst.getB() - 1);
    }*/

    return 0;
}


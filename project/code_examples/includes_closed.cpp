#include <iostream>
#include <vector>

using namespace std;

class A{
private:
    int a;
    int b;

public:
    A(int a, int b) {
        this->a = a;
        this->b = b;
    }

    setA(int a) { this->a = a; }
    setB(int b) { this->b = b; }

    getA() { return a; }
    getB() { return b; }
};

int main() {
    vector<int> vec;

    A inst(1, 2);

    while (inst.getB()) {
        inst.setA(inst.getA() + 1);
        inst.setB(inst.getB() - 1);
    }

    for (int i = 0; i < 10; i++)
        vec.push_back(i);
    return 0;
}



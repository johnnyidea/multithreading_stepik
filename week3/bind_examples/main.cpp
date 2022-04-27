#include <iostream>
#include <math.h>
#include <functional>

using namespace std;
using namespace placeholders;

double f(double a, double b, double c, double d) {

    cout << a/b + log(c) + exp(d) << endl;
    return a/b + log(c) + exp(d);
}

int main()
{

    auto g = std::bind(f, 0, 1, _1, _1);
//    cout << g(3) << endl;

//    cout << log(11) << endl;
    auto g1 = std::bind<int>(f, _1, _2, _3, _4);
//    cout << g1(0, 1 , 2, 3) << endl;
//    auto g = std::bind(f, _1, _2, _1, _1);
    auto g3 = std::bind<int>(f, 1, -1, _1, 0);
//    cout << g3(11, 12) << endl;
    auto g4 = std::bind(f, _2, _1, _3, _4);
//    cout << g4(1, 2, 3, 4) << endl;
    auto g5 = std::bind(f, 0, 1, 1, 0);
//    cout << g5() << endl;
    auto g6 = std::bind(f, -1, 1, 1, 0);
    cout << g6() << endl;
//    auto g = std::bind<int>(f, 1, 1, exp(1), _1);
//    auto g = std::bind(f, _1, 2, 1, _2);

    std::cout << "Hello, World!" << std::endl;
    return 0;
}


#include <stdio.h>
#include <iostream>
#include <cassert>
#include <unordered_set>
#include <unordered_map>
#include <map>

using namespace std;

unsigned int f(unsigned int n) {

    if(n == 0) return 1;

    else if(n == 1) return 1;

    return f(n-2) + f(n-1);

}

std::string derivative(std::string polynomial)
{
    string res;

    map<int, int> deriv_exp;

    size_t pos = 0;
    std::string token;

    while ((pos = polynomial.find("x")) != std::string::npos)
    {
        int end_member{0};

        for (end_member  = pos; end_member < polynomial.size(); end_member++)
            if (polynomial[end_member] == '+' || polynomial[end_member] == '-')
                break;

        token = polynomial.substr(0, end_member);

        auto pos_pwr = token.find("^");
        auto pos_mult = token.find("*");
        int coef {1};

        if (pos_pwr != std::string::npos)
        {
            auto power = stoi(token.substr(pos_pwr + 1, token.size()));

            if (pos_mult != std::string::npos)
                coef = stoi(token.substr(0, pos_mult)) * power;
            else if (token[0] == '-')
                coef = -1 * power;
            else
                coef = power;

            if (deriv_exp.count(--power) > 0)
                deriv_exp[power] += coef;
            else
                deriv_exp.emplace(power, coef);

        } else if (pos_mult != std::string::npos)
        {
            coef = stoi(token.substr(0, pos_mult));

            if (deriv_exp.count(1) > 0)
                deriv_exp[1] += stoi(token.substr(0, pos_mult));
            else
                deriv_exp[0] += coef;
        } else if (deriv_exp.count(0) > 0)
        {
            if (token[0] == '-')
                deriv_exp[0] -= 1;
            else
                deriv_exp[0] += 1;
        }
        else if (token[0] == '-')
            if (deriv_exp.count(0) > 0)
                deriv_exp[0] -= 1;
            else
                deriv_exp.emplace(0, -1);
        else
            deriv_exp.emplace(0, 1);

        polynomial.erase(0, token.size());
    }

    for (auto it = deriv_exp.rbegin(); it != deriv_exp.rend(); it++)
    {
        if (it != deriv_exp.rbegin() && it->second > 0)
            res.append( "+" );

        res.append( to_string(it->second));

        if (it->first == 0)
            continue;

        res.append( "*x");

        if (it->first > 1)
            res.append( "^" + to_string(it->first));
    }

    if (res.empty())
        res = "0";

    return res;
}


class StringPointer
{
public:
    StringPointer()
    :t(nullptr)
    {}

    std::string *operator->()
    {
        return t;
    }

    ~StringPointer()
    {
        if (!t)
            delete t;
    }

    operator std::string*()
    {
        return t;
    }
    StringPointer(std::string *Pointer)
    {
        if (Pointer)
            t = Pointer;
        else
            t = new string();
    }

private:
    string* t;
};


using namespace std;

class SmallAllocator
{
public:
    SmallAllocator(): mem_change(0){};

    void* Alloc(unsigned int Size)
    {
        mem_change += Size;

        if (mem_change < sz)
            return static_cast<void*>(static_cast<char*>(Memory) + mem_change - Size);
        else
            return nullptr;
    };

    void *ReAlloc(void *Pointer, unsigned int Size)
    {
        if (mem_change + Size > sz)
            return nullptr;

        for (int i = 0; i < Size; i++)
            *(Memory + mem_change + i) = *(static_cast<char*>(Pointer) + i);

        mem_change += Size;

        return static_cast<void*>(static_cast<char*>(Memory) + mem_change - Size);
    };

    void Free(void *Pointer)
    {
        if (!Pointer)
            delete Pointer;
    };

private:
    uint mem_change;
    static constexpr uint sz{1048576};
    char Memory[sz];
};

int main(int argc, char **argv)
{
    {
        SmallAllocator A1;
        int *A1_P1 = (int *) A1.Alloc(sizeof(int));
        A1_P1 = (int *) A1.ReAlloc(A1_P1, 2 * sizeof(int));
        A1.Free(A1_P1);
    }
    SmallAllocator A2;
    int * A2_P1 = (int *) A2.Alloc(10 * sizeof(int));
    for(unsigned int i = 0; i < 10; i++)
        A2_P1[i] = i;
    for(unsigned int i = 0; i < 10; i++)
        if(A2_P1[i] != i)
            std::cout << "ERROR 1" << std::endl;
    int * A2_P2 = (int *) A2.Alloc(10 * sizeof(int));
    for(unsigned int i = 0; i < 10; i++)
        A2_P2[i] = -1;
    for(unsigned int i = 0; i < 10; i++)
        if(A2_P1[i] != i)
            std::cout << "ERROR 2" << std::endl;
    for(unsigned int i = 0; i < 10; i++)
        if(A2_P2[i] != -1)
            std::cout << "ERROR 3" << std::endl;

    A2_P1 = (int *) A2.ReAlloc(A2_P1, 20 * sizeof(int));
    for(unsigned int i = 10; i < 20; i++)
        A2_P1[i] = i;
    for(unsigned int i = 0; i < 20; i++)
        if(A2_P1[i] != i)
            std::cout << "ERROR 4" << std::endl;

    for(unsigned int i = 0; i < 10; i++)
        if(A2_P2[i] != -1)
            std::cout << "ERROR 5" << std::endl;

    A2_P1 = (int *) A2.ReAlloc(A2_P1, 5 * sizeof(int));

    for(unsigned int i = 0; i < 5; i++)
        if(A2_P1[i] != i)
            std::cout << "ERROR 6" << std::endl;

    for(unsigned int i = 0; i < 10; i++)
        if(A2_P2[i] != -1)
            std::cout << "ERROR 7" << std::endl;

    A2.Free(A2_P1);
    A2.Free(A2_P2);

//    std::string s1 = "Hello, world!";
//
//    StringPointer sp1(&s1);
//    StringPointer sp2(NULL);
//
//    std::cout << sp1->length() << std::endl;
//    std::cout << *sp1 << std::endl;
//    std::cout << sp2->length() << std::endl;
//    std::cout << *sp2 << std::endl;

//    std::string p1 {"2*x^100-100*x^2"};
//    assert("200*x^99-200*x" == derivative(p1));
//
//    std::string p2 {"x+x+x+x+x+x+x+x+x+x"};
//    assert("10" == derivative(p2));
//
//    std::string p3 {"x^10000+x+1"};
//    assert("10000*x^9999+1" == derivative(p3));
//
//    std::string p4 {"-x^2-x^3"};
//    assert("-3*x^2-2*x" == derivative(p4));
//
//
//    string p5("x^2+x");
//    assert("2*x+1" == derivative(p5) );
//
//
//    string p6("2");
//    assert("0" == derivative(p6) );
//
//
//    string p7("x");
//    assert("1" == derivative(p7) );
//
//
//    string p8("-x");
//    assert("-1" == derivative(p8) );
//
//
//    string p9("-x-x-x");
//    assert("-3" == derivative(p9) );
//
//    string p10("5*x");
//    assert("5" == derivative(p10) );
//
//    string p11("10*x-9*x");
//    assert("1" == derivative(p11) );

//    unsigned int n;
//
//    scanf("%u", &n);
//
//    n = f(n);
//
//    printf("f(n) = %u\n", n);

    return 0;

}
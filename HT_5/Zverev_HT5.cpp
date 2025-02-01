#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// делаем реверс
class Reverser 
{
public:
    template<typename Container>
    void operator()(Container& c) 
    {
        reverse(c.begin(), c.end());
    }
};

// для печати
template<typename T>
void print(const T& c) 
{
    for (const auto& elem : c) 
        cout << elem << " ";
    cout << "\n";
}

// основная функция
int main() 
{
    Reverser rev;

    list<int> L = {1, 2, 3, 4, 5};
    rev(L);
    print(L);

    vector<int> V = {1, 2, 3, 4, 5};
    rev(V);
    print(V);

    string str = "abcdef";
    rev(str);
    print(str);

    return 0;
}
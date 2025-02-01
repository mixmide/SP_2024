#include <iostream>
using namespace std;

// описываем класс Matrix
class Matrix
{
// дружественный оператор << (описан ниже)
friend ostream & operator << (ostream &print, const Matrix &matrix);

public:
    // конструктор - инициализируем матрицу размера m x n (по умолч. m = n = 5)
    Matrix(unsigned int m = 5, unsigned int n = 5)
    {
        size_m = m;
        size_n = n;
        elem = new int[m*n];
        for(int i = 0; i < m*n; i++)
        {
            elem[i] = 0;
        }
    }
    // деструктор - очищаем память
    ~Matrix() { delete[]elem; }
    // оператор [] для получения указателя на нужную строку
    int* operator[] (int index) { return &elem[index*size_m]; }
    // --//-- (аналогично для const)
    const int* operator[](int index) const { return &elem[index*size_m]; }

private:
    unsigned int size_m = 0;    // размер матрицы - число строк
    unsigned int size_n = 0;    // размер матрицы - число столбцов
    int *elem = nullptr;        // матрица
};

// оператор выдачи на экран
ostream & operator << (ostream &print, const Matrix &matrix)
{
    for(int i = 0; i < matrix.size_m; i++)
    {
        for(int j = 0; j < matrix.size_n; j++)
        {
            print << matrix.elem[i*matrix.size_m + j] << " ";
        }
        print << "\n";
    }
    return print;
}

int main()
{
    // замечание: нумерация столбцов и строк идет с нуля!
    Matrix m;
    const Matrix mc;
    m[1][2] = 5;
    cout << m << mc;
    int x = m[2][3];
    //cout << "\n";              // для удобства чтения результатов
    cout << x << endl;
    cout << mc[1][1];
    //cout << "\n";              // для удобства чтения результатов
    //mc[1][1] = 100;            // вызовет ошибку!
    return 0;
}
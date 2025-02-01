#include <iostream>
#include <string>
#include <vector>
using namespace std;

// класс ЖИВОТНОЕ - содержит 2 виртуальные функции
class Animal 
{
public:
    virtual void name_fun() const = 0;   // имя животного
    virtual void age_fun() const = 0;    // возраст животного
};


// производный класс СОБАКА
class Dog : public Animal 
{
public:
    Dog(const string& n, int a) : name(n), age(a)   // конструктор
    {
    }

    void name_fun() const override     // переопределение функции name_fun()
    {
        cout << "DOG: " << name << "\t";
    }

    void age_fun() const override      // переопределение функции age_fun()
    {
        cout << "AGE: " << age << "\t\t";
    }
private:
    string name;                       // кличка собаки
    int age;                           // возраст собаки
};


// производный класс КОШКА
class Cat : public Animal 
{
public:
    Cat(const string& n, int a) : name(n), age(a)   // конструктор
    {
    }

    void name_fun() const override     // переопределение функции name_fun()
    {           
        cout << "CAT: " << name << "\t";
    }

    void age_fun() const override      // переопределение функции age_fun()
    {
        cout << "AGE: "<< age << "\t\t";
    }
private:
    string name;                       // кличка кошки
    int age;                           // возраст кошки
};


// независимый класс ДОМ - работает с массивом объектов типа класса ЖИВОТНОЕ
class House 
{
public:
    House()                                 // конструктор
    {
        cout << "------------HOUSE------------\n";
    }

    void add_animal(Animal* animal)         // добавление животного в дом
    {
        animals.push_back(animal);
    }

    void all_names()                        // печать имен всех животных
    {    
        for (Animal* animal : animals) 
        {
            animal->name_fun();
        }
        cout << "\n";
    }

    void all_ages()                         // печать возрастов всех животных
    {
        for (Animal* animal : animals) 
        {
            animal->age_fun();
        }
        cout << "\n";
    }

    ~House()                                // деструктор
    {    
        for (Animal* animal : animals) 
        {
            delete animal;
        }
    }
private:
    vector<Animal*> animals;   // вектор (массив) указателей на объекты-ЖИВОТНОЕ
};


// ОСНОВНАЯ ФУНКЦИЯ
int main() 
{
    House house;                              // создаем объект класса ДОМ
    house.add_animal(new Dog("Alex", 3));     // добавляем в дом собаку Alex, 3 года
    house.add_animal(new Cat("Barsik", 6));   // добавляем в дом кота Barsik, 6 лет
    house.all_names();                        // печать инф-ии об именах всех животных 
    house.all_ages();                         // печать инф-ии о возрасте всех животных
    return 0;
}

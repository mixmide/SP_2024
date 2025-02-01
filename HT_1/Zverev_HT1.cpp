#include <iostream>
#include <cstring>
using namespace std;

// КЛАСС ОБЪЕКТОВ "БАНКОВСКИЙ СЧЁТ"
class bank_account {
    public:
        bank_account()
        // конструктор если список аргументов пуст
        {
            number = 0;
            owner = new char[1];
            owner[0] = '\0';
            date = 0;
            sum = 0;
            cout << "Constructor_with_empty_arguments completed!\n";
        }
        bank_account(const unsigned long int number1, const char* owner1, const unsigned long int date1, const long int sum1)
        // конструктор если заданы все аргументы в классическом виде
        {
            number = number1;
            owner = new char[strlen(owner1) + 1];
            strcpy(owner, owner1);
            date = date1;
            sum = sum1;
            cout << "Constructor_with_arguments with number: " << number << " completed!\n";
        }
        bank_account(const bank_account & buf)              
        // конструктор если аргумент это объект класса
        {
            number = buf.number;
            owner = new char[strlen(buf.owner) + 1];
            strcpy(owner, buf.owner);
            date = buf.date;
            sum = buf.sum;
            cout << "Constructor_duplicate completed!\n";
        }
        bank_account & operator= (const bank_account & buf) 
        // оператор присваивания
        {
            number = buf.number;
            delete[] owner;
            owner = new char[strlen(buf.owner) + 1];
            strcpy(owner, buf.owner);
            date = buf.date;
            sum = buf.sum;
            cout << "Operator worked!\n";
            return *this;
        }
        ~bank_account()
        // деконструктор
        {
            cout << "Destructor " << owner << " loading...";
            delete[] owner;
            owner = nullptr;
            cout << " completed!\n";
        }
        void edit(const unsigned long int number1, const char* owner1, const unsigned long int date1, const long int sum1)
        // редактор
        {
            cout << "Editor loading...";
            number = number1;
            if(owner1 != nullptr)
            {
                delete[] owner;
                owner = new char[strlen(owner1) + 1];
                strcpy(owner, owner1);
            }
            date = date1;
            sum = sum1;
            cout << " completed!\n";
        }
        unsigned long int get_number()
        // геттер номера счёта
        {
            cout << "get_number launched!\n";
            return number;
        }
        char* get_owner()
        // геттер владельца
        {
            cout << "get_owner launched!\n";
            char* owner_out = new char[strlen(owner) + 1];
            strcpy(owner_out, owner);
            return owner_out;
        }
        unsigned long int get_date()
        // геттер даты
        {
            cout << "get_date launched!\n";
            return date;
        }
        long int get_sum()
        // геттер суммы
        {
            cout << "get_sum launched!\n";
            return sum;
        }
        void master_get()
        // "геттер" для всех данных одновременно - просто печатает всю инф-ю об объекте
        {
            cout << "\nnumber: " << number << "\nowner: " << owner << "\ndate: " << date << "\nsum: " << sum << endl;
        }
    private: 
        // переменные класса, храним их в закрытой для внешнего доступа секции!
        unsigned long int number;
        char* owner;
        unsigned long int date;
        long int sum;
};


// КЛАСС ОБЪЕКТОВ - ДВУНАПРАВЛЕННЫЙ СПИСОК ИЗ ОБЪЕКТОВ "БАНКОВСКИЙ СЧЁТ"
class list {
    public:
        list()      
        // конструктор (здесь для него не нужны аргументы)
        {
            cout << "list_object started!\n";
        }
        ~list()     
        // деконструктор - корректно уничтожаем все объекты
        {
            struct_list* buf = nullptr;
            while(start != nullptr)
            {
                buf = start;
                start = start->next;
                delete buf->data;       // удаление объекта "банковский счет"
                delete buf;             // удаление элемента списка
            }
        }
        void push_front(const bank_account & elem)
        // добавление нового элемента в начало списка
        {
            struct_list* buf = new struct_list;
            buf->data = new bank_account;
            *(buf->data) = elem;
            if(start == nullptr)             // список пуст?
            {
                start = buf;
                end = buf;
                buf->next = nullptr;
                buf->prev = nullptr;
            }
            else
            {
                buf->next = start;
                start = buf;
                buf->prev = nullptr;
                buf->next->prev = start;
            }
        }
        void push_back(const bank_account & elem)
        // добавление нового элемента в конец списка - аналогично ф-ии выше
        {
            struct_list* buf = new struct_list;
            buf->data = new bank_account;
            *(buf->data) = elem;
            if(start == nullptr)
            {
                start = buf;
                end = buf;
                buf->next = nullptr;
                buf->prev = nullptr;
            }
            else
            {
                buf->prev = end;
                end = buf;
                buf->next = nullptr;
                buf->prev->next = end;
            }
        }
        bank_account* front()
        // чтение первого эл-та
        {
            if(start == nullptr)
                return nullptr;
            else {
                bank_account* buf = new bank_account(*(start->data)); // соблюдаем приватность!
                return buf;
            }
        }
        bank_account* back()
        // чтение последнего эл-та - аналогично ф-ии выше
        {
            if(start == nullptr)
                return nullptr;
            else {
                bank_account* buf = new bank_account(*(end->data)); // соблюдаем приватность!
                return buf;
            }
        }
        void pop_front()
        // удаление первого эл-та
        {
            this->erase(1);
        }
        void pop_back()
        // удаление последнего эл-та
        {
            this->erase(this->size());
        }
        void insert(const bank_account & elem, int p)
        // добавление элемента перед позицией p
        {
            if (p <= 0) {
                cout << "insert error: p <= 0\n";
                return;
            }
            if (start == nullptr)
            {
                cout << "insert error: empty list!\n";
                return;
            }
            struct_list* buf = start;
            for (int i = 1; i < p; i++)
            {
                if (buf->next == nullptr) {
                    cout << "insert error: p is too mach for this list!\n";
                    return;
                }
                buf = buf->next;
            }
            struct_list* new_elem = new struct_list;
            new_elem->data = new bank_account;
            *(new_elem->data) = elem;
            new_elem->prev = buf->prev;
            new_elem->next = buf;
            if (new_elem->prev != nullptr)
                new_elem->prev->next = new_elem;
            buf->prev = new_elem;
        }
        void erase(int p)
        // функция удаления эл-та из позиции p
        {
            if (p <= 0) {
                cout << "erase error: p <= 0\n";
                return;
            }
            if (start == nullptr)
            {
                cout << "erase error: empty list!\n";
                return;
            }
            struct_list* buf = start;
            for (int i = 1; i < p; i++)
            {   
                if (buf->next == nullptr) {
                    cout << "erase error: p is too mach for this list!\n";
                    return;
                }
                buf = buf->next;
            }
            if (buf->next != nullptr)
                buf->next->prev = buf->prev;
            else
                end = buf->prev;
            if (buf->prev != nullptr)
                buf->prev->next = buf->next;
            else
                start = buf->next;
            delete buf->data;
            delete buf;
        }
        void empty()
        // функция проверка на пустоту списка
        {
            if(start == nullptr)
                cout << "empty list!\n";
            else
                cout << "no empty list!\n";
        }
        int size()
        // функция-подсчет кол-ва эл-в в списке
        {
            struct_list* buf = start;
            int counter = 0;
            while(buf != nullptr)
            {
                buf = buf->next;
                counter++;
            }  
            return counter;
        } 
        void print()
        // функция вывод инф-ии обо всех эл-х списка
        {
            if (start == nullptr)
            {
                cout << "no info: empty list!" << endl;
                return;
            }
            struct_list* buf = start;
            while(buf != nullptr)
            {
                cout << "ELEMENT - info:\n";
                buf->data->master_get();
                buf = buf->next;
            }  
        }
    private:
        // переменные класса, храним их в закрытой для внешнего доступа секции!
        struct struct_list
        {
            bank_account* data = nullptr;
            struct_list* next = nullptr;
            struct_list* prev = nullptr;
        };
        struct_list* start = nullptr;
        struct_list* end = nullptr;
};



// ГЛАВНАЯ ФУНКЦИЯ
int main(void)
{
    // реализация задания_1 - тест
    bank_account first(1234, "mixmide", 623, 100);
    first.master_get();
    bank_account second(first);
    second.edit(12345, "nikita", 135, 200);
    second.master_get();
    bank_account third;
    third.edit(123456, "lol_kek", 111, 300);
    third.master_get();
    cout << "\n\n\n";

    // реализация задания_2 - тест: последовательно пробуем выполнять все ф-ии в
    //                              соответствии с их порядком в условии задания
    list List1;
    List1.push_front(first);
    List1.push_back(second);
    List1.front();
    List1.back();
    List1.pop_front();
    List1.pop_back();
    List1.insert(first, 1);
    List1.erase(1);
    List1.empty();
    cout << List1.size() << " elements in list\n";
    List1.print();
    return 0;
}
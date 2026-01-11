#include <iostream>
#include <vector>
#include <string>
#include <bitset>

#include "identities.h"
#include "keli_and_ordered.h"

// КОНСТАНТЫ
const int MAX_RANK = 8; 
const int MIN_RANK = 2; 

// ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ

// Заполняет вектор всеми операциями
void fill(std::vector<std::string> &vec)
{
    for(int i = 0; i <= 255; i++)
    {
        vec.push_back(std::bitset<8>(i).to_string());
    }
}

// проверяет операцию на формат 0000'xxxx или xxxx'0000
bool detect_4_zeroes(std::vector<std::string>::iterator it)
{
    int count = 0;
    // Проверка на 0000'xxxx
    for(int i = 0; i < 4; i++)
    {
        if((*it)[i] == '0')
        {
            count++;
            if(count == 4) return true;
        }
        else count = 0;
    }

    count = 0;
    // Проверка на xxxx'0000
    for(int i = 4; i < 8; i++)
    {
        if((*it)[i] == '0')
        {
            count++;
            if(count == 4) return true;
        }
        else count = 0;
    }

    return false;
}

// Выводит все операции вектора операций
void display(std::vector<std::string> &vec) 
{
    for(std::string s : vec)
    {
        std::cout << s << '\n';
    }
}

int bin_to_int(std::string str)
{
    return std::stoi(str, nullptr, 2);
}

// ОПЕРАЦИИ НАД F
std::string F_d(std::string O) // меняет местами I и II
{
    std::string tmp = "";
    tmp += O.substr(4, 8);
    tmp += O.substr(0, 4);
    return tmp;
}

std::string F_c(std::string O) // главная диагональ для I - 0 и 3; для II - 4, 7
{
    std::string tmp = F_d(O);
    char t = tmp[0];
    tmp[0] = tmp[3];
    tmp[3] = t;

    t = tmp[4];
    tmp[4] = tmp[7];
    tmp[7] = t;
    return tmp;
}

std::string F_f(std::string O) // F_d и F_c или F_c и F_d
{
    std::string tmp = F_c(F_d(O));
    return tmp;
}

// КЛАСС ОПЕРАЦИЙ
class F_classes 
{
    friend bool operator==(const F_classes& L, const F_classes& R);
    public:
        void _fill(std::string);
        bool _is_in_class(std::string);
        void _display();
        int _number();
        int _rank();
        std::vector<int> _get_I();
        std::vector<int> _get_II();
        std::string _get_F();
    private:
        std::string F, Fd, Ff, Fc;
};

// МЕТОДЫ КЛАССА
// Отображает содержимое класса (УЛУЧШИТЬ)
void F_classes::_display()
{
    std::cout << '\n';
    std::cout << F << '\t' << Fd << '\n';
    std::cout << Ff << '\t' << Fc << '\n';
    std::cout << '\n';
}

// Заполняет класс операцией О (строит F, Fc, Fd, Ff из O)
void F_classes::_fill(std::string O)
{
    F = O;
    Fd = F_d(O);
    Ff = F_f(O);
    Fc = F_c(O);
}

// Проверяет, нет ли операции О в классе
bool F_classes::_is_in_class(std::string O)
{
    return (O == F) || (O == Fd) || (O == Ff) || (O == Fc);
}

// Перегрузка оператора сравнения
bool operator==(const F_classes& L, const F_classes& R)
{
    return (L.F == R.F) && (L.Fd == R.Fd) && (L.Ff == R.Ff) && (L.Fc == R.Fc);
}

// Конвертирует операцию в число
int F_classes::_number()
{
    return bin_to_int(F);
}

// Возвращает ранк I и II операции класса (ОПТИМИЗИРОВАТЬ \ РАЗГОВНОКОДИТЬ)
int F_classes::_rank()
{
    int rankL = 0, rankR=0;
    for(int i = 0; i < 4; i++)
    {
        rankL += F[i] == '1' ? 1 : 0;
    }

    for(int i = 4; i < 8; i++)
    {
        rankR += F[i] == '1' ? 1 : 0;
    }

    return rankL + rankR;
}

// Возвращает I часть в виде вектора (нужно для таблицы Кэли)
std::vector<int> F_classes::_get_I()
{
    std::vector<int> I{};
    for(int i = 0; i < 4; i++)
    {
        I.push_back(F[i] - '0'); // Выражение F[i] - '0' равносильно ('1'|'0') - '0' или (49|48) - 48, что равно (1|0). Тип char - просто число от 0 до 255, отображаемое как символ ASCII.
    }

    return I;

}

// Возвращает II часть в виде вектора (нужно для таблицы Кэли)
std::vector<int> F_classes::_get_II()
{
    std::vector<int> II{};
    for(int i = 4; i < 8; i++)
    {
        II.push_back(F[i] - '0'); // Выражение F[i] - '0' равносильно ('1'|'0') - '0' или (49|48) - 48, что равно (1|0). Тип char - просто число от 0 до 255, отображаемое как символ ASCII.
    }

    return II;

}

std::string F_classes::_get_F()
{
    return F;
}

// (xy)z = x(yz) (ТОЛЬКО НА ВЫЯВЛЕНИЕ АССОЦИАТИВНОСТИ)
bool associative_iden(std::array<std::array<int, 16>, 16> K)
{
    bool res = true;
    for(int x = 0; x < 16; x++)
    {
        for(int y = 0; y < 16; y++)
        {
            for(int z = 0; z < 16; z++)
            {
                int xy = K[x][y];
                int xyz1 = K[xy][z];

                int yz = K[y][z];
                int xyz2 = K[x][yz];

                res = xyz1 == xyz2 ? true : false;
                if(!res){return false;}
            }
        }
    }
    return true;
}

// Проверяет класс на ассоциативность
bool is_associative(F_classes X)
{
    std::vector<int> I, II;

    I = X._get_I();
    II = X._get_II();

    // По данной таблице Кэли, построенной для I и II части операции, проверяются тождества.
    // Тождество не выполняется, если хотя бы для каких-то элементов оно не выполняется. В противном случае выполняется.
    std::array<std::array<int, 16>, 16> K = construct_keli(I, II);

    // Тождество ассоциативности
    if(associative_iden(K))
        return true; // ассоциативно
    
    return false; // не ассоциативно
}

int main()
{

    // здесь происходит проверка тождеств на заданных операциях (увы, операции надо записывать руками)
    std::vector<std::string> vec_operations = 
    {
        "01000100",
        "01100110",
        "11001100",
        "11011101",
        "11111111",
        "10011001",
        "01100100",
        "11000100",
        "11010100",
        "11110100",
        "11110110",
        "10000100",
        "10010100",
        "10010110",
        "10011100",
        "10011111",
        "10011101",
        "10001100",
        "11011100",
        "11111100",
        "11111101",
        "11000101",
        "01101101"

    };

    for(std::string O : vec_operations)
    {
        F_classes cls;
        cls._fill(O);

        std::vector<int> I = cls._get_I(), II = cls._get_II();

        auto Keli = construct_keli(I, II);
        auto Ordered = construct_ordered();

        std::cout << "\nПроверка тождеств для:\t" << cls._get_F() << '\n';

        if(is_associative(cls)){std::cout << "0 ";}
        if(iden1(Keli)){std::cout << "1 ";}
        if(iden2(Keli)){std::cout << "2 ";}
        if(iden3(Keli)){std::cout << "3 ";}
        if(iden4(Keli)){std::cout << "4 ";}
        if(iden4_star(Keli)){std::cout << "4* ";}
        if(iden5(Keli)){std::cout << "5 ";}
        // if(iden5_star(Keli)){std::cout << "5* ";}
        if(iden6(Keli, Ordered)){std::cout << "6 ";}
        if(iden6_star(Keli, Ordered)){std::cout << "6* ";}
        if(iden7(Keli, Ordered)){std::cout << "7 ";}
        if(quasi_iden8(Keli, Ordered)){std::cout << "8 ";}
        if(quasi_iden9(Keli, Ordered)){std::cout << "9 ";}
        if(quasi_iden10(Keli, Ordered)){std::cout << "10 ";}
        // if(quasi_iden10_star(Keli, Ordered)){std::cout << "10* ";}
        if(quasi_iden11(Keli, Ordered)){std:: cout << "11 ";}

        std::cout << "\n\n";
    }

    // здесь просто генерируются всевозможные классы операций
    // а так же устранение классов операций вида 0000'xxxx или xxxx'0000
    // std::vector<std::string> vec_all_operations{};
    // fill(vec_all_operations);

    // for(std::vector<std::string>::iterator it = vec_all_operations.begin(); it != vec_all_operations.end(); it++)
    // {
    //     if(detect_4_zeroes(it))
    //     {
    //         vec_all_operations.erase(it);
    //         --it;
    //     }
    // }


    // здесь происходит отбор уникальных классов
    // std::vector<F_classes> vec_unique_classes{};
    // for(std::string O : vec_all_operations)
    // {
    //     if(vec_unique_classes.empty())
    //     {
    //         F_classes F;
    //         F._fill(O);
    //         vec_unique_classes.push_back(F);
    //     }
    //     else
    //     {
    //         for(F_classes F : vec_unique_classes)
    //         {
    //             if(F._is_in_class(O)) break;
    //             else if(F == vec_unique_classes.back() && F._is_in_class(O) == false)
    //             {
    //                 F_classes Fi;
    //                 Fi._fill(O);
    //                 vec_unique_classes.push_back(Fi);
    //             }
    //         }
    //     }
    // }


    // здесь происходит сортировка классов операций по рангу (или ранку). От меньшего к большемую.
    // std::vector<F_classes> vec_sorted_unique_classes{};
    // for(int rank = ::MIN_RANK ; rank <= ::MAX_RANK ; rank++)
    // {
    //     for(F_classes F : vec_unique_classes)
    //     {
    //         if(F._rank() == rank)
    //         {
    //             vec_sorted_unique_classes.push_back(F);
    //         }
    //     }
    // }



    // // СОЗДАТЬ ВЫВОД В ФАЙЛ!!!
    // for(F_classes F : vec_sorted_unique_classes)
    // {
    //     std::cout << "Класс операций под номером " << F._number() << " и рангом " << F._rank();
    //     F._display();
    // }

    // Поиск всех ассоциативных классов
    // std::vector<F_classes> vec_associative_classes{};
    // for(F_classes F : vec_sorted_unique_classes)
    // {
    //     if(is_associative(F))
    //         vec_associative_classes.push_back(F);
    // }

    // for(F_classes F : vec_associative_classes)
    // {
    //     std::cout << "Класс операций под номером " << F._number() << " и рангом " << F._rank();
    //     F._display();
    // }

    return 0;
}

// ПРОБЛЕМА: положение единиц в I и II иногда совпадает со всеми операциями в классе (т.е. F = Fc = Fd = Ff)

// TODO: Добавить всевозможные комбинации операций меньшего ранга для получения операции ранга N.
// Пример: вывести все комбинации операций ранга 1 и 2, с помощью которых строится ранг 3.

// Алгоритм:
// === КОДИРОВКА ОПЕРАЦИЙ ДВОИЧНЫМИ ЧИСЛАМИ ===
//  Создать контейнер с операциями
//  Заполнить контейнер всевозможными операциями от 0000 0000 до 1111 1111 (где левая часть - первая под-операция, правая часть - вторая под-операция)
//  Выкинуть все операции, которые имеют вид 0000 xxxx или xxxx 0000
//  Операции вида O_bin сопоставить номер N_int, построенный из bin -> int
//  Из первой операции O_bin строить класс операций F_n = {F, F_d, F_f, F_c} (контейнер с операциями)
//  F - бинарная операция
//  F_d - двойственная операция к операции F (меняются местами левая и правая часть операции)
//  F_c - операция взятия обратного к операции F (петли меняются местами)
//  F_f - сопряженная операция к операции F (это F_d и F_c одновременно)
//  Вторую операцию O_bin проверить следующим образом:
//     Если O_bin содержится в ЛЮБОМ классе F_n, то рассматриваем следующую операцию O_bin (нельзя строить класс из операции, которая содержится в другом классе)
//     Иначе строим следующий класс F_n из операции O_bin


//  ЗАПЛАНИРОВАНО:
//  Форматируем построенные классы:
//  Вводим массив 3х3 для табличной визуализации. (???)
//  Если в классе F_n какие-то из операций совпадают между собой (сравнивать по bin/int виду)
//   Заменяем их на прочерк - и знак равенства = между теми операциями, с которыми они совпадают.
//   Ставим знак неравенства/равенства для соседних операций, которые не совпадают/совпадают.
//   Визуализируем класс F_n
//  Иначе (все операции в классе различны и не совпадают по bin/int)
//   Визуализируем класс F_n
// ХИТРОСТЬ: представлять все операции в классе как INT для упрощения сравнения "на глаз".

// ВЫЯВЛЕНИЕ ТОЖДЕСТВ НА КЛАССАХ
// 1. Найти ассоциативные классы по первичным тождествам, должно быть 24 класса. Если выполняются все первичные тождества - класс ассоциативный.
// 2. Для каждого класса проверяем вторичные тождества (записываем номера выполненных тождеств в класс или просто выводим их?)
// АЛГОРИТМ
// 1. Завести vec_associative_classes.
// 2. Проверяем каждый класс из vec_unique_classes (через функцию?). Если ВСЕ выполнились - записываем в vec_associative_classes
// 3. Каждый класс из vec_associative_classes проверяем на вторичных тождествах. Выполненное тождество запоминаем (записываем в класс или выводим) 
// ПРОВЕРЯТЬ ПО ТАБЛИЦЕ КЭЛИ!!!
// Необходимо разбить F на I и II операцию, по которым затем строится таблица Кэли.




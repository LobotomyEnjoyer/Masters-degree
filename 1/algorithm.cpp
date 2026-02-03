#include <iostream>
#include <vector>
#include <string>
#include <bitset>

#include "identities.h"
#include "keli_and_ordered.h"
#include "old_identities.h"
#include "F_classes.h"

// КОНСТАНТЫ
const int MAX_RANK = 8; 
const int MIN_RANK = 2; 

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

// Для DEBUG'а, позволяет вывести матрицу Кэли или Порядка для просмотра их значений.
void display_array(std::array<std::array<int,16>,16> M)
{
        std::cout << "    ";
        for(int i = 0; i < 16; i++)
        {
            std::cout << i << (i < 10 ? "    " : "   ");
        }
        std::cout<<'\n';

        for(int i = 0; i < 16; i++)
        {
            std::cout<<i<<(i < 10 ? "   " : "  ");
            for(int e : M[i])
            {
                std::cout << e << (e < 10 ? "    " : "   ");
            }
            std::cout << '\n';
    }
}

int main()
{
    // ЧЕРНЫЙ СПИСОК КОДОВ
    std::vector<std::string> vec_blacklist = 
    {
        "00010001",
        "10001000"
    };

    // здесь происходит проверка тождеств на заданных операциях (увы, операции надо записывать руками)
    std::vector<std::string> vec_operations = 
    {
        // КОДЫ ИЗ ГРАНТОВ
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



        // КОДЫ ИЗ МОЕГО ДИПЛОМА
        // "01000110",
        // "01100100",

        // "01001001",
        // "10010100",

        // "01001100",
        // "11000100",

        // "01001010",
        // "10100100",

        // "00100110",
        // "01100010",

        // "00101001",
        // "10010010",

        // "00101100",
        // "11000010",

        // "00101010",
        // "10100010",

        // "10000110",
        // "01101000",

        // "10001001",
        // "10011000",

        // "10001100",
        // "11001000",

        // "10000101",
        // "01011000",

        // "10001010",
        // "10101000",

        // "10000011",
        // "00111000",
        
        

    };

    for(std::string O : vec_operations)
    {
        F_classes cls;
        cls._fill(O);

        std::vector<int> I = cls._get_I(), II = cls._get_II();

        auto Keli = construct_keli(I, II);
        auto Ordered = construct_ordered();

        // display_array(Keli);
        
        std::cout << "\nПроверка тождеств для:\t" << cls._get_F() << " типа " << cls._get_type() << " и ранга " << cls._get_rank() <<'\n';

        // КОД ДЛЯ ПРОВЕРКИ ТОЖДЕСТВ ПО ГРАНТАМ
        if(is_associative(cls)){std::cout << "0 ";}
        if(iden1(Keli)){std::cout << "1 ";}
        if(iden2(Keli)){std::cout << "2 ";}
        if(iden3(Keli)){std::cout << "3 ";}
        if(iden4(Keli)){std::cout << "4 ";}
        if(iden4_star(Keli)){std::cout << "4* ";}
        if(iden5(Keli)){std::cout << "5 ";}
        if(iden6(Keli, Ordered)){std::cout << "6 ";}
        if(iden6_star(Keli, Ordered)){std::cout << "6* ";}
        if(iden7(Keli, Ordered)){std::cout << "7 ";}
        if(quasi_iden8(Keli, Ordered)){std::cout << "8 ";}
        if(quasi_iden9(Keli, Ordered)){std::cout << "9 ";}
        if(quasi_iden10(Keli, Ordered)){std::cout << "10 ";}
        if(quasi_iden11(Keli, Ordered)){std:: cout << "11 ";}

        // КОД ДЛЯ ПРОВЕРКИ ТОЖДЕСТВ ИЗ МОЕГО ДИПЛОМА
        // if(i1(Keli)){std::cout << "1 ";}
        // if(i2(Keli)){std::cout << "2 ";}
        // if(i3(Keli)){std::cout << "3 ";}
        // if(i4(Keli)){std::cout << "4 ";}
        // if(i5(Keli)){std::cout << "5 ";}
        // if(i6(Keli)){std::cout << "6 ";}
        // if(i7(Keli)){std::cout << "7 ";}
        // if(i8(Keli)){std::cout << "8 ";}
        // if(i9(Keli)){std::cout << "9 ";}
        // if(i10(Keli, Ordered)){std::cout << "10 ";}
        // if(i11(Keli, Ordered)){std::cout << "11 ";}
        // if(qi12(Keli, Ordered)){std::cout << "12 ";}
        // if(qi13(Keli, Ordered)){std::cout << "13 ";}
        // if(qi14(Keli, Ordered)){std::cout << "14 ";}

        std::cout << "\n\n";
    }

    // здесь просто генерируются всевозможные классы операций
    // а так же устранение классов операций вида 0000'xxxx или xxxx'0000, а так же из черного списка
    // std::vector<std::string> vec_all_operations{};
    // fill(vec_all_operations);

    // for(std::vector<std::string>::iterator it = vec_all_operations.begin(); it != vec_all_operations.end(); it++)
    // {
    //     if(detect_4_zeroes(it) || (*it) == vec_blacklist[0] || (*it) == vec_blacklist[1])
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


    // здесь происходит сортировка классов операций по рангу (или ранку). От меньшего к большему.
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

    // std::cout << vec_sorted_unique_classes.size() << '\n'; // выводит количество уникальных классов
    // std::cout << vec_all_operations.size() << '\n'; // выводит количество всевозможных классов

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




#include <iostream>
#include <vector>
#include <string>
#include <bitset>

void fill(std::vector<std::string> &vec)
{
    for(int i = 0; i <= 255; i++)
    {
        vec.push_back(std::bitset<8>(i).to_string());
    }
}


bool check(std::vector<std::string>::iterator it)
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

void display(std::vector<std::string> &vec)
{
    for(std::string s : vec)
    {
        std::cout << s << '\n';
    }
}

int main()
{
    std::vector<std::string> vec_operations{};


    fill(vec_operations);

    for(std::vector<std::string>::iterator it = vec_operations.begin(); it != vec_operations.end(); it++)
    {
        if(check(it))
        {
            vec_operations.erase(it);
            --it;
        }
    }

    display(vec_operations);
    return 0;
}

// Алгоритм:
// === ДВОИЧНЫМИ ЧИСЛАМИ ===
//  Создать контейнер с операциями
//  Заполнить контейнер всевозможными операциями от 0000 0000 до 1111 1111 (где левая часть - первая под-операция, правая часть - вторая под-операция)
//  Выкинуть все операции, которые имеют вид 0000 xxxx или xxxx 0000
//  Операции вида O_bin сопоставить номер N_int, построенный из bin -> int
//  Из первой операции O_bin строить класс операций F_n = {F, F_d, F_f, F_c} (контейнер с операциями)
//  Вторую операцию O_bin проверить следующим образом:
//     Если O_bin содержится в ЛЮБОМ классе F_n, то рассматриваем следующую операцию O_bin (нельзя строить класс из операции, которая содержится в другом классе)
//     Иначе строим следующий класс F_n из операции O_bin
//  Форматируем построенные классы:
//  Вводим массив 3х3 для табличной визуализации. (???)
//  Если в классе F_n какие-то из операций совпадают между собой (сравнивать по bin/int виду)
//   Заменяем их на прочерк - и знак равенства = между теми операциями, с которыми они совпадают.
//   Ставим знак неравенства/равенства для соседних операций, которые не совпадают/совпадают.
//   Визуализируем класс F_n
//  Иначе (все операции в классе различны и не совпадают по bin/int)
//   Визуализируем класс F_n
 
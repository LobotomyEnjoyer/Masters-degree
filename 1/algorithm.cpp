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


bool remove_4_zeroes(std::vector<std::string>::iterator it)
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

void display(std::vector<std::string> &vec) // выводит все операции вектора операций
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
    private:
        std::string F, Fd, Ff, Fc;
};

// МЕТОДЫ КЛАССА
void F_classes::_display()
{
    std::cout << '\n';
    std::cout << F << '\t' << Fd << '\n';
    std::cout << Ff << '\t' << Fc << '\n';
    std::cout << '\n';
}

void F_classes::_fill(std::string O)
{
    F = O;
    Fd = F_d(O);
    Ff = F_f(O);
    Fc = F_c(O);
}

bool F_classes::_is_in_class(std::string O)
{
    return (O == F) || (O == Fd) || (O == Ff) || (O == Fc);
}

bool operator==(const F_classes& L, const F_classes& R)
{
    return (L.F == R.F) && (L.Fd == R.Fd) && (L.Ff == R.Ff) && (L.Fc == R.Fc);
}

int F_classes::_number()
{
    return bin_to_int(F);
}

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




int main()
{
    std::vector<std::string> vec_all_operations{};
    fill(vec_all_operations);

    for(std::vector<std::string>::iterator it = vec_all_operations.begin(); it != vec_all_operations.end(); it++)
    {
        if(remove_4_zeroes(it))
        {
            vec_all_operations.erase(it);
            --it;
        }
    }

    std::vector<F_classes> vec_unique_classes{};
    for(std::string O : vec_all_operations)
    {
        if(vec_unique_classes.empty())
        {
            F_classes F;
            F._fill(O);
            vec_unique_classes.push_back(F);
        }
        else
        {
            for(F_classes F : vec_unique_classes)
            {
                if(F._is_in_class(O)) break;
                else if(F == vec_unique_classes.back() && F._is_in_class(O) == false)
                {
                    F_classes Fi;
                    Fi._fill(O);
                    vec_unique_classes.push_back(Fi);
                }
            }
        }
    }

    for(F_classes F : vec_unique_classes)
    {
        std::cout << "Класс операций под номером " << F._number() << " и рангом " << F._rank();
        F._display();
    }


    return 0;
}

// ПРОБЛЕМА: ранг и положение единиц в I и II иногда совпадает со всеми операциями

// Алгоритм:
// === ДВОИЧНЫМИ ЧИСЛАМИ ===
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
//  Форматируем построенные классы:
//  Вводим массив 3х3 для табличной визуализации. (???)
//  Если в классе F_n какие-то из операций совпадают между собой (сравнивать по bin/int виду)
//   Заменяем их на прочерк - и знак равенства = между теми операциями, с которыми они совпадают.
//   Ставим знак неравенства/равенства для соседних операций, которые не совпадают/совпадают.
//   Визуализируем класс F_n
//  Иначе (все операции в классе различны и не совпадают по bin/int)
//   Визуализируем класс F_n
 
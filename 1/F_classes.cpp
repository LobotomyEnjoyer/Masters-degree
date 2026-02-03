#include <string>
#include <bitset>
#include <vector>
#include <iostream>

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
        int _get_rank();
        std::vector<int> _get_I();
        std::vector<int> _get_II();
        std::string _get_F();
        char _get_type();
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
int F_classes::_get_rank()
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

char F_classes::_get_type()
{
    if((F == Fd) && (F == Fc) && (F == Ff)){return 'A';}
    else if((F == Ff) && (Fc == Fd)){return 'B';}
    else if((F == Fd) && (Fc == Ff)){return 'C';}
    else if((F == Fc) && (Fd == Ff)){return 'D';}
    else{return 'E';}
}
#include <iostream>
#include <bitset>
#include <string>
#include <array>
#include <vector>
#include <algorithm>


// десятичное(целое) в двоичное(строка)
std::string dec_to_bin(int x)
{ 
    return std::bitset<4>(x).to_string();
}

// двоичное(строка) в десятичное(целое)
int binvec_to_int(std::vector<int> x)
{ 
    std::string S(""); // строка из битов, т.е. 0 и 1 длиною в 4 символа
    for(int i = 0; i < x.size(); i++){
        // char chr = x[i] ? char(49) : char(48);
        char chr = x[i] ? '1' : '0';
        S.push_back(chr);
    }
    return std::bitset<4>(S).to_ulong();
}

// разбиение двоичной строки длины 4 на вектор из двух подстрок длины 2.
std::vector<std::string> _div(std::string a)
{ 
    std::vector<std::string> x(2); 
    for(int i = 0; i < 4; i++){
        i < 2 ? x[0].push_back(a[i]) : x[1].push_back(a[i]);
    }
    return x;
}


// функция для сравнения (используется для построения таблицы Кэли)
bool _comparison(std::vector<int> A, std::vector<std::string> c, int& k, int& l)
{ 
    int t = A.size();
    std::array<bool, 4> flags = {};
    for(int i = 0; i < t; i++){
        int x1 = i < 2 ? k : l;
        int x2 = i%2 == 0 ? k : l;
        if(A[i] == 0 || int(c[x1][x2]) == 49){flags[i] = true;}
        else{flags[i] = false;}
    }

    bool result = std::all_of(flags.cbegin(), flags.cend(), [](bool k){return k == true;});
    return result;
}

// строит таблицу Кэли (принимает два параметра, представляющих I и II часть бинарной операции)
std::array<std::array<int,16>,16> construct_keli(std::vector<int> A, std::vector<int> B){
    int t[16] = {}; // набор чисел 0-15
    for(int i = 0; i < 16; i++){
        t[i] = i;
    }

    std::array<std::array<int,16>,16> K{-1};

    for(int i : t){
        for(int j : t){
            std::string a = dec_to_bin(i);
            std::string b = dec_to_bin(j);
            std::vector<int> W(0); // пустой числовой вектор W
            std::vector<std::string> c = _div(a);
            std::vector<std::string> d = _div(b);
            for(int k = 0; k < 2; k++){
                for(int l = 0; l < 2; l++){
                    bool cond_A = _comparison(A, c, k, l);
                    bool cond_B = _comparison(B, d, k, l);
                    cond_A && cond_B ? W.push_back(1) : W.push_back(0);
                }
            }
            K[i][j] = binvec_to_int(W);
        }
    }

    return K;

}

// проверяет на наличие порядка вида ≤, т.е.
// 0011 0101 - нет порядка
// 0100 0111 - есть порядок
// сравниваются каждые позиции двух двоичных значений.
// Если у левого значения на i-й позиции стоит 1, а у правого 0, то порядок нарушен.
bool is_ordered(int x, int y){
    std::string A = dec_to_bin(x);
    std::string B = dec_to_bin(y);
    bool flag = 1;

    for(int i = 0; i<4; i++){
        flag = A[i] <= B[i] ? 1 : 0;
        if(flag == 0){return flag;}
    }
    return flag;

}

// строит матрицу порядка
std::array<std::array<int,16>,16> construct_ordered(){
    int t[16] = {};
    for(int i = 0; i<16; i++){
        t[i] = i;
    }

    std::array<std::array<int,16>,16> O {-1};

    for(int i : t){
        for(int j : t){
            O[i][j] = is_ordered(i,j); 
        }
    }
    return O;
}
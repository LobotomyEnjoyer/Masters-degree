#include <iostream>
#include <bitset>
#include <string>
#include <array>
#include <vector>
#include <algorithm>

std::string dec_to_bin(int x){ // десятичное(целое) в двоичное(строка)
    return std::bitset<4>(x).to_string();
}

int bin_to_dec(std::vector<int> x){ // двоичное(строка) в десятичное(целое)
    std::string S; // строка из битов, т.е. 0 и 1 длиною в 4 символа
    for(int i = 0; i < x.size(); i++){
        char chr = x[i] ? char(49) : char(48);
        S.push_back(chr);
    }
    return std::bitset<4>(S).to_ulong();
}

std::vector<std::string> _div(std::string a){ // разбиение двоичной строки длины 4 на вектор из двух подстрок длины 2.
    std::vector<std::string> x(2); 
    for(int i = 0; i < 4; i++){
        i < 2 ? x[0].push_back(a[i]) : x[1].push_back(a[i]);
    }
    return x;
}

bool _comparison(std::vector<int> A, std::vector<std::string> c, int& k, int& l){ // функция для сравнения
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

std::array<std::array<int,16>,16> algorithm(std::vector<int> A, std::vector<int> B){
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
            K[i][j] = (bin_to_dec(W));
        }
    }

    return K;

}

bool is_ordered(int x, int y){
    std::string A = dec_to_bin(x);
    std::string B = dec_to_bin(y);
    bool flag = 1;

    for(int i = 0; i<4; i++){
        flag = A[i] <= B[i] ? 1 : 0;
        if(flag == 0){break;}
    }
    return flag;

}

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
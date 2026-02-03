#ifndef F_CLASSES_H
#define F_CLASSES_H

#include<vector>
#include<iostream>
#include<string>

void fill(std::vector<std::string> &vec);

bool detect_4_zeroes(std::vector<std::string>::iterator it);

void display(std::vector<std::string> &vec);

std::string F_d(std::string O);

std::string F_c(std::string O);

std::string F_f(std::string O);

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


#endif
#include <iostream>
#include "../include/task3.h"

namespace lab {
    complex_num complex_num::operator+(complex_num &cn) const {
        return complex_num(this->_real + cn._real, this->_unreal + cn._unreal);
    }

    complex_num &complex_num::operator+=(complex_num &cn) {
        this->_real += cn._real;
        this->_unreal += cn._unreal;
        return *this;
    }

    complex_num complex_num::operator-(complex_num &cn) const {
        return complex_num(this->_real - cn._real, this->_unreal - cn._unreal);
    }

    complex_num &complex_num::operator-=(complex_num &cn) {
        this->_real -= cn._real;
        this->_unreal -= cn._unreal;
        return *this;
    }

    complex_num complex_num::operator*(complex_num const &cn) const {
        return complex_num(this->_real * cn._real - this->_unreal * cn._unreal,
                           this->_real * cn._unreal + this->_unreal * cn._real);
    }

    complex_num &complex_num::operator*=(complex_num const &cn) {
        double real_temp = this->_real * cn._real - this->_unreal * cn._unreal;
        double unreal_temp = this->_real * cn._unreal + this->_unreal * cn._real;

        this->_real = real_temp;
        this->_unreal = unreal_temp;

        return *this;
    }

    complex_num complex_num::operator/(complex_num const &cn) const {
        double sq_sum = cn._real * cn._real + cn._unreal * cn._unreal;
        return complex_num((this->_real * cn._real + this->_unreal * cn._unreal) / sq_sum,
                           (this->_unreal * cn._real - this->_real * cn._unreal) / sq_sum);
    }

    complex_num &complex_num::operator/=(complex_num const &cn) {
        double sq_sum = cn._real * cn._real + cn._unreal * cn._unreal;
        double real_temp = (this->_real * cn._real + this->_unreal * cn._unreal) / sq_sum;
        double unreal_temp = (this->_unreal * cn._real - this->_real * cn._unreal) / sq_sum;

        this->_real = real_temp;
        this->_unreal = unreal_temp;

        return *this;
    }

    [[nodiscard]] double complex_num::abs() const {
        return std::sqrt(this->_real * this->_real + this->_unreal * this->_unreal);
    }

    [[nodiscard]] double complex_num::arg() const {
        return std::atan2(this->_unreal, this->_real);
    }
}
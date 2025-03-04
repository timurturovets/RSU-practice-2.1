#include <cmath>
#include <iostream>

class complex_num {
public:
    explicit complex_num(double real = 0.0, double unreal = 0.0) {
        _real = real;
        _unreal = unreal;
    }

    complex_num operator +(complex_num &cn) const {
        return complex_num(this->_real + cn._real, this->_unreal + cn._unreal);
    }

    complex_num& operator += (complex_num &cn) {
        this->_real += cn._real;
        this->_unreal += cn._unreal;
        return *this;
    }

    complex_num operator -(complex_num &cn) const {
        return complex_num(this->_real - cn._real, this->_unreal - cn._unreal);
    }

    complex_num& operator -=(complex_num &cn) {
        this->_real -= cn._real;
        this->_unreal -= cn._unreal;
        return *this;
    }

    complex_num operator *(complex_num const &cn) const {
        return complex_num(this->_real * cn._real - this->_unreal * cn._unreal,
                           this->_real * cn._unreal + this->_unreal * cn._real);
    }

    complex_num& operator *=(complex_num const &cn) {
        double real_temp = this->_real * cn._real - this->_unreal *cn._unreal;
        double unreal_temp = this->_real * cn._unreal + this->_unreal * cn._real;

        this->_real = real_temp;
        this->_unreal = unreal_temp;

        return *this;
    }

    complex_num operator /(complex_num const &cn) const {
        double sq_sum = cn._real * cn._real + cn._unreal * cn._unreal;
        return complex_num((this->_real * cn._real + this->_unreal * cn._unreal) / sq_sum,
                           (this->_unreal * cn._real - this->_real * cn._unreal) / sq_sum);
    }

    complex_num &operator /=(complex_num const &cn) {
        double sq_sum = cn._real * cn._real + cn._unreal * cn._unreal;
        double real_temp = (this->_real * cn._real + this->_unreal * cn._unreal) / sq_sum;
        double unreal_temp = (this->_unreal * cn._real - this->_real * cn._unreal) / sq_sum;

        this->_real = real_temp;
        this->_unreal = unreal_temp;

        return *this;
    }

    [[nodiscard]] double abs() const {
        return std::sqrt(this->_real * this->_real + this->_unreal * this->_unreal);
    }

    [[nodiscard]] double arg() const {
        return std::atan2(this->_unreal, this->_real);
    }

    friend std::ostream& operator <<(std::ostream &os, complex_num const &cn) {
        os << cn._real;
        if (cn._unreal >= 0) os << "+";
        os << cn._unreal << "i";
        return os;
    }

    friend std::istream& operator >>(std::istream &is, complex_num &cn) {
        is >> cn._real >> cn._unreal;
        return is;
    }

private:
    double _real;
    double _unreal;
};
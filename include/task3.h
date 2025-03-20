#include <cmath>
#include <iostream>
namespace lab {
    class complex_num {
    public:
        explicit complex_num(double real = 0.0, double unreal = 0.0) {
            _real = real;
            _unreal = unreal;
        }

        ~complex_num() noexcept = default;

        complex_num(complex_num const &cn) = default;

        complex_num &operator=(complex_num const &cn) = default;

        complex_num operator+(complex_num &cn) const {
            return complex_num(this->_real + cn._real, this->_unreal + cn._unreal);
        }

        complex_num &operator+=(complex_num &cn);

        complex_num operator-(complex_num &cn) const;

        complex_num &operator-=(complex_num &cn);

        complex_num operator*(complex_num const &cn) const;

        complex_num &operator*=(complex_num const &cn);

        complex_num operator/(complex_num const &cn) const;
        complex_num &operator/=(complex_num const &cn);

        [[nodiscard]] double abs() const;

        [[nodiscard]] double arg() const;

        friend std::ostream &operator<<(std::ostream &os, complex_num const &cn) {
            os << cn._real;
            if (cn._unreal >= 0) os << "+";
            os << cn._unreal << "i";
            return os;
        }

        friend std::istream &operator>>(std::istream &is, complex_num &cn) {
            is >> cn._real >> cn._unreal;
            return is;
        }

    private:
        double _real;
        double _unreal;
    };
}
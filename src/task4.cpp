#include "../include/task4.h"

namespace lab {
    real_matrix::real_matrix(size_t const rows, size_t const cols) : _rows(rows), _cols(cols) {
        this->_m = new double *[_rows];
        for (size_t i = 0; i < _rows; i++) {
            (*this)[i] = new double[_cols];
            for (size_t j = 0; j < _cols; j++) {
                (*this)[i][j] = 0;
            }
        }
    }

    real_matrix::real_matrix(real_matrix const &rm) : _rows(rm._rows), _cols(rm._cols) {
        _m = new double *[rm._rows];
        for (size_t i = 0; i < rm._rows; i++) {
            (*this)[i] = new double[rm._cols];
            for (size_t j = 0; j < rm._cols; j++) {
                (*this)[i][j] = rm[i][j];
            }
        }
    }

    real_matrix &real_matrix::operator=(real_matrix const &rm) {
        if (&rm == this) return *this;

        for (size_t i = 0; i < _rows; i++) {
            delete[] _m[i];
        }

        delete[] _m;

        _m = new double *[rm._rows];
        for (size_t i = 0; i < rm._rows; i++) {
            (*this)[i] = new double[rm._cols];
            for (size_t j = 0; j < rm._cols; j++) {
                (*this)[i][j] = rm[i][j];
            }
        }

        return *this;
    }

    real_matrix::~real_matrix() noexcept {
        for (size_t i = 0; i < this->_rows; i++) {
            delete[] this->_m[i];
        }
        delete[] this->_m;
    }

    double *&real_matrix::operator[](size_t row) const {
        if (row >= this->_rows) throw index_out_of_range_exception();
        return this->_m[row];
    }

    real_matrix real_matrix::operator+(real_matrix const &rm) const {
        if (this->_rows != rm._rows || this->_cols != rm._cols) throw matrices_sizing_unequal_exception();

        real_matrix new_rm(this->_rows, this->_cols);

        for (size_t i = 0; i < this->_rows; i++) {
            for (size_t j = 0; j < this->_cols; j++) {
                new_rm[i][j] = (*this)[i][j] + rm[i][j];
            }
        }

        return new_rm;
    }

    real_matrix real_matrix::operator-(real_matrix const &rm) const {
        if (this->_rows != rm._rows || this->_cols != rm._cols) throw matrices_sizing_unequal_exception();

        real_matrix new_rm(this->_rows, this->_cols);

        for (size_t i = 0; i < this->_rows; i++) {
            for (size_t j = 0; j < this->_cols; j++) {
                new_rm[i][j] = this->_m[i][j] - rm._m[i][j];
            }
        }

        return new_rm;
    }

    real_matrix real_matrix::operator*(real_matrix const &rm) const {
        if (this->_cols != rm._rows) throw matrices_sizing_unmatched_exception();

        real_matrix new_rm(this->_cols, rm._rows);

        for (size_t i = 0; i < this->_rows; i++) {
            for (size_t j = 0; j < rm._cols; j++) {
                for (size_t k = 0; k < this->_cols; k++) {
                    new_rm[i][j] = this->_m[i][k] * rm._m[k][j];
                }
            }
        }

        return new_rm;
    }

    real_matrix real_matrix::operator*(double num) const {
        for (size_t i = 0; i < this->_rows; i++) {
            for (size_t j = 0; j < this->_cols; j++) {
                this->_m[i][j] *= num;
            }
        }

        return *this;
    }

    [[nodiscard]] real_matrix real_matrix::transpose() const {
        real_matrix transposed(this->_cols, this->_rows);

        for (size_t i = 0; i < this->_cols; i++) {
            for (size_t j = 0; j < this->_rows; j++) {
                transposed[i][j] = this->_m[j][i];
            }
        }

        return transposed;
    }

    [[nodiscard]] double real_matrix::determinant() const {
        if (this->_rows != this->_cols) throw non_square_matrix_exception();

        double d = 1.0;
        real_matrix temp = *this;

        for (size_t i = 0; i < temp._rows; i++) {
            size_t row_with_max = i;
            for (size_t j = i + 1; j < temp._rows; j++) {
                if (fabs(temp._m[j][i]) > fabs(temp._m[row_with_max][i])) {
                    row_with_max = j;
                }
            }

            if (temp._m[row_with_max][i] == 0) throw singular_matrix_exception();

            if (row_with_max != i) {
                real_matrix::swap_rows(temp, i, row_with_max);
                d *= -1;
            }

            for (size_t j = i + 1; j < temp._rows; j++) {
                double frac = temp[j][i] / temp[i][i];
                for (size_t k = i; k < temp._cols; k++) {
                    temp[j][k] -= frac * temp[i][k];
                }
            }

            d *= temp[i][i];
        }

        return d;
    }

    [[nodiscard]] real_matrix real_matrix::get_inverse() const {
        if (this->_rows != this->_cols) throw non_square_matrix_exception();
        if (determinant() == 0) throw singular_matrix_exception();

        real_matrix inverse(this->_rows, this->_cols);

        real_matrix aux(this->_rows, this->_cols * 2);
        for (size_t i = 0; i < this->_rows; i++) {
            for (size_t j = 0; j < this->_rows; j++) {
                aux[i][j] = (*this)[i][j];
            }
            aux[i][i + this->_rows] = 1;
        }

        for (size_t i = 0; i < this->_rows; i++) {
            size_t row_with_max = i;
            for (size_t j = i + 1; j < this->_rows; j++) {
                if (fabs(aux[j][i]) > fabs(aux[row_with_max][i])) row_with_max = j;
            }

            real_matrix::swap_rows(aux, i, row_with_max);

            for (size_t j = i + 1; j < this->_rows * 2; j++) {
                aux[i][j] /= aux[i][i];
            }
            aux[i][i] = 1;

            double frac;
            for (size_t j = 0; j < this->_rows; j++) {
                if (j == i) continue;

                frac = aux[j][i];
                for (size_t k = i; k < this->_rows * 2; k++) {
                    aux[j][k] -= frac * aux[i][k];
                }
            }
        }

        for (size_t i = 0; i < this->_rows; i++) {
            for (size_t j = 0; j < this->_rows; j++) {
                inverse[i][j] = aux[i][j + this->_rows];
            }
        }

        return inverse;
    }
}
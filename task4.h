#include <cstdio>
#include <stdexcept>
#include <cmath>

class real_matrix {
private:
    double **_m;
    size_t _rows;
    size_t _cols;

    static real_matrix &swap_rows(real_matrix &rm, size_t r1, size_t r2) {
        if (r1 >= rm._rows || r2 >= rm._rows) throw index_out_of_range_exception();

        double temp;
        for(size_t i = 0; i < rm._rows; i++) {
            temp = rm[r1][i];
            rm[r1][i] = rm[r2][i];
            rm[r2][i] = temp;
        }

        return rm;
    }

public:
    class non_square_matrix_exception : public std::exception {
    public:
        [[nodiscard]] const char *what() const noexcept override {
            return "This matrix is not square";
        }
    };

    class singular_matrix_exception : public std::exception {
    public:
        [[nodiscard]] const char *what() const noexcept override {
            return "This matrix is singular";
        }
    };

    class index_out_of_range_exception : public std::exception {
    public:
        [[nodiscard]] const char *what() const noexcept override {
            return "Couldn't access item: index out of range";
        }
    };

    class matrices_sizing_unequal_exception : public std::exception {
    public:
        [[nodiscard]] const char *what() const noexcept override {
            return "Matrices sizes are unequal";
        }
    };

    class matrices_sizing_unmatched_exception : public std::exception {
    public:
        [[nodiscard]] const char *what() const noexcept override {
            return "Matrices sizing don't match";
        }
    };

    real_matrix(size_t const rows, size_t const cols) :_rows(rows), _cols(cols) {
        this->_m = new double*[_rows];
        for (size_t i = 0; i < _rows; i++) {
            this->_m[i] = new double[_cols];
            for (size_t j = 0; j < _cols; j++) {
                this->_m[i][j] = 0;
            }
        }
    }

    real_matrix(real_matrix const &rm) = default;
    real_matrix &operator =(real_matrix const &rm) = default;
    ~real_matrix() noexcept {
        for (size_t i = 0; i < this->_rows; i++) {
            delete [] this->_m[i];
        }
        delete [] this->_m;
    }

    double *operator [](size_t row) const {
        if (row >= this->_rows) throw index_out_of_range_exception();
        return this->_m[row];
    }

    real_matrix operator +(real_matrix const &rm) const {
        if (this->_rows != rm._rows || this->_cols != rm._cols) throw matrices_sizing_unequal_exception();

        real_matrix new_rm(this->_rows, this->_cols);

        for (size_t i = 0; i < this->_rows; i++) {
            for (size_t j = 0; j < this->_cols; j++) {
                new_rm[i][j] = (*this)[i][j] + rm[i][j];
            }
        }

        return new_rm;
    }

    real_matrix operator -(real_matrix const &rm) const {
        if (this->_rows != rm._rows || this->_cols != rm._cols) throw matrices_sizing_unequal_exception();

        real_matrix new_rm(this->_rows, this->_cols);

        for (size_t i = 0; i < this->_rows; i++) {
            for (size_t j = 0; j < this->_cols; j++) {
                new_rm[i][j] = this->_m[i][j] - rm._m[i][j];
            }
        }

        return new_rm;
    }

    real_matrix operator *(real_matrix const &rm) const {
        if (this->_cols != rm._rows) throw matrices_sizing_unmatched_exception();

        real_matrix new_rm(this->_cols, rm._rows);

        for (size_t i = 0; i < this->_rows; i++) {
            for (size_t j = 0; j < rm._cols; j++) {
                for(size_t k = 0; k < this->_cols; k++) {
                    new_rm[i][j] = this->_m[i][k] * rm._m[k][j];
                }
            }
        }

        return new_rm;
    }

    real_matrix operator *(double num) const {
        for (size_t i = 0; i < this->_rows; i++) {
            for (size_t j = 0; j < this->_cols; j++) {
                this->_m[i][j] *= num;
            }
        }

        return *this;
    }

    friend real_matrix operator *(double num, real_matrix const &rm) {
        return rm * num;
    }

    [[nodiscard]] real_matrix transpose() const {
        real_matrix transposed(this->_cols, this->_rows);

        for (size_t i = 0; i < this->_cols; i++) {
            for (size_t j = 0; j < this->_rows; j++) {
                transposed[i][j] = this->_m[j][i];
            }
        }

        return transposed;
    }

    [[nodiscard]] double determinant() const {
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

            if(temp._m[row_with_max][i] == 0) throw singular_matrix_exception();

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

    [[nodiscard]] real_matrix get_inverse() const {
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
            for(size_t j = 0; j < this->_rows; j++) {
                inverse[i][j] = aux[i][j + this->_rows];
            }
        }

        return inverse;
    }
};
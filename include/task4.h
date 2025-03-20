#include <cstdio>
#include <stdexcept>
#include <cmath>

namespace lab {
    class real_matrix {
    private:
        double **_m;
        size_t _rows;
        size_t _cols;

        static real_matrix &swap_rows(real_matrix &rm, size_t r1, size_t r2) {
            if (r1 >= rm._rows || r2 >= rm._rows) throw index_out_of_range_exception();

            double temp;
            for (size_t i = 0; i < rm._rows; i++) {
                temp = rm[r1][i];
                rm[r1][i] = rm[r2][i];
                rm[r2][i] = temp;
            }

            return rm;
        }

    public:
        real_matrix(size_t rows, size_t cols);

        real_matrix(real_matrix const &rm);

        real_matrix &operator=(real_matrix const &rm);

        ~real_matrix() noexcept;

        double *&operator[](size_t row) const;

        real_matrix operator+(real_matrix const &rm) const;

        real_matrix operator-(real_matrix const &rm) const;

        real_matrix operator*(real_matrix const &rm) const;

        real_matrix operator*(double num) const;

        friend real_matrix operator*(double num, real_matrix const &rm) {
            return rm * num;
        }

        [[nodiscard]] real_matrix transpose() const;

        [[nodiscard]] double determinant() const;

        [[nodiscard]] real_matrix get_inverse() const;

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
    };
}


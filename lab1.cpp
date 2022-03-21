#include <iostream>
#include <string>
#include <stdexcept>
#include <regex>

template <class T>
class matrix_row {
public:
    matrix_row(int size) {
        this->length = size;
        this->row = new T[size]{ 0 };
    };

    T& operator [](int i) {
        if (i < length) {
            return row[i];
        }
        throw std::out_of_range("");
    };

    matrix_row<T>* clone() {
        matrix_row<T>* clone = new matrix_row<T>(length);
        for (int i = 0; i < length; i++) {
            (*clone)[i] = row[i];
        }
        return clone;
    }

    matrix_row<T>* clone(matrix_row<T>* instance, bool castSize = false) {
        if (castSize) {
            (*instance).length = length;
            instance->row = new T[this->length]{ 0 };
        }
        else {
        
            if (instance->length != this->length) {
                throw std::exception("not same size");
            }
        }
        for (int i = 0; i < length; i++) {
            (*instance)[i] = row[i];
        }
        return instance;
    }

    void operator*=(double multiplier) {
        for (int i = 0; i < this->length; i++) {
            this->row[i] *= multiplier;
        }
    };

    bool isEmpty() {
        for (int i = 0; i < this->length; i++) {
            if (row[i] != 0) {
                return false;
            }
        }
        return true;
    }

    void operator-=(matrix_row<T>* row) {

        if (this->length == row->length) {
            for (int i = 0; i < this->length; i++) {
                float value = this->row[i] - (*row)[i];
                this->row[i] = value;
            }
        }
        else {
            throw std::out_of_range("not same size");
        }
    };

    void normalizeAt(int index) {
        if (index < length) {
            double divider = row[index];
            for (int i = 0; i < length; i++) {
                row[i] /= divider;
            }
        }
        else {
            throw std::out_of_range("");
        }
    }

    void print() {
        for (int i = 0; i < this->length; i++) {
            std::cout << this->row[i] << " ";
        }
    };

private:
    T* row;
    int length;
};

template <class T>
class matrix {
public:
    matrix(int row, int column) {

        this->column = column;
        this->row = row;

        rows = new matrix_row<double> * [row];
        for (int i = 0; i < row; i++) {
            rows[i] = new matrix_row<double>(column);
        }
    }

    int countNonEmptyRows() {
        int result = 0;
        for (int i = 0; i < row; i++) {
            if (!(rows[i]->isEmpty())) {
                result++;
            }
        }
        return result;
    }

    void stdRead() {

        static const std::regex exp("^[+-]?[0-9]+(\\.[0-9]+)?$");
        std::string str;

        for (int j = 0; j < row; j++) {
            T* result = new T[this->column]{ 0 };
            for (int i = 0; i < column; i++) {
                std::cin >> str;
                if (!std::regex_match(str, exp)) {
                    std::cout << "\"" << str << "\" was skipped\n";
                    i--;
                }
                else {
                    result[i] = (T)std::stod(str);
                }
            }
            for (int l = 0; l < this->column; l++) {
                (*(rows[j]))[l] = result[l];
            }
            delete[] result;
        }
    }

    matrix_row<double>*& operator [](int i) {
        if (i < this->row) {
            return rows[i];
        }
        throw std::out_of_range("");
    };

    void print() {
        for (int i = 0; i < row; i++) {
            rows[i]->print();
            std::cout << "\n";
        }
    }

    void toLinearIndependency(bool showSteps = false) {
        int j = 0;
        int index = 0;
        matrix_row<double>* clone = NULL;// = new matrix_row<double>(1); // <===
        for (int i = 0; i < column; i++) {
            index = this->findRow(j, i);
            if (index != -1) {
                this->swapRows(index, j);
                (*((*this)[j])).normalizeAt(i);
                for (int l = (j + 1); l < row; l++) {
                    double multiplier = (*((*this)[l]))[i];
                    //matrix_row<double>* clone = (*((*this)[j])).clone();
                    if (clone) { (*((*this)[j])).clone(clone, true); }
                    else { clone = (*((*this)[j])).clone(); }
                    (*clone) *= multiplier;
                    (*((*this)[l])) -= clone;
                    //delete clone;
                }
                if (showSteps) {
                    (*this).print();
                }
                j++;
            }

        }
        delete[] clone;
    }

private:
    matrix_row<double>** rows;
    int column;
    int row;

    int findRow(int startRow, int startColumn) {

        for (int i = startRow; i < this->row; i++) {
            if ((*(rows[i]))[startColumn] != 0) {
                return i;
            }
        }
        return -1;

    }

    void swapRows(int row_1, int row_2) {
        matrix_row<double>* tmp = rows[row_1];
        rows[row_1] = rows[row_2];
        rows[row_2] = tmp;
    }
};

int getInt() {
    std::string str;
    const std::regex exp("^[1-9]([0-9]+)?$");
    do { std::cin >> str; } while (!std::regex_match(str, exp));
    return stoi(str);
}

int main() {

    std::cout << "enter matrix size: \n";

    int rows = getInt();
    int columns = getInt();

    matrix<float> mx(rows, columns);

    mx.print();


    std::cout << "\nenter matrix:\n";

    std::cin.clear();
    std::cin.ignore(INT_MAX, '\n');

    mx.stdRead();

    std::cout << "\n";

    mx.print();

    mx.toLinearIndependency(); // debug
    int rank = mx.countNonEmptyRows();

    std::cout << "\n" << "result:" << rank;
}


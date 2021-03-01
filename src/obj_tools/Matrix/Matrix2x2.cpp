
#include "Matrix2x2.hpp"

#define MAX_ROWS 2
#define MAX_COLS 2

using namespace obj_tools;

Matrix2x2::Matrix2x2(void) {
    this->elements_[0][0] = 1;
    this->elements_[0][1] = 0;
    this->elements_[1][0] = 0;
    this->elements_[1][1] = 1;
}

Matrix2x2::Matrix2x2(float elements[2][2]) {
    for    (int i = 0; i < MAX_ROWS; i++) {
        for(int j = 0; j < MAX_COLS; j++) {
            this->elements_[i][j] = elements[i][j];
        }
    }
}

Matrix2x2::Matrix2x2(const Matrix2x2& m) {
    for    (int i = 0; i < MAX_ROWS; i++) {
        for(int j = 0; j < MAX_COLS; j++) {
            this->elements_[i][j] = m.elements_[i][j];
        }
    }
}

Matrix2x2& Matrix2x2::operator =(float elements[2][2]) {
    for    (int i = 0; i < MAX_ROWS; i++) {
        for(int j = 0; j < MAX_COLS; j++) {
            this->elements_[i][j] = elements[i][j];
        }
    }

    return *this;
}

Matrix2x2& Matrix2x2::operator =(const Matrix2x2& m){
    for    (int i = 0; i < MAX_ROWS; i++) {
        for(int j = 0; j < MAX_COLS; j++) {
            this->elements_[i][j] = m.elements_[i][j];
        }
    }

    return *this;
}

float Matrix2x2::getElement(const int& row, const int& col) {
    int r = (row >= MAX_ROWS) ? MAX_ROWS - 1 : row;
    int c = (col >= MAX_COLS) ? MAX_COLS - 1 : col;

    r = (r < 0) ? 0 : r;
    c = (c < 0) ? 0 : c;

    return this->elements_[r][c];
}

void Matrix2x2::setElement(const int& row, const int& col, const float& value) {
    int r = (row >= MAX_ROWS) ? MAX_ROWS - 1 : row;
    int c = (col >= MAX_COLS) ? MAX_COLS - 1 : col;

    r = (r < 0) ? 0 : r;
    c = (c < 0) ? 0 : c;

    this->elements_[r][c] = value;
}


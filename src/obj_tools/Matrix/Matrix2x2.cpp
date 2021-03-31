
#include "Matrix2x2.hpp"
#include "../Math/Math.hpp"
#include <math.h>

#define MAX_ROWS 2
#define MAX_COLS 2
#define MIN_INCREMENT 1e-6

using namespace obj_tools;

Matrix2x2 OBJ_TOOLS_EXPORT obj_tools::operator * (const float& s, const Matrix2x2& m) {
    Matrix2x2 res;

    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            res.elements_[i][j] = s * m.elements_[i][j];
        }
    }
    return res;
}

Matrix2x2 Matrix2x2::createRotateMatrix(const double& rad) {
    Matrix2x2 res;

    res.setElement(0, 0, (float)cos(rad));
    res.setElement(0, 1, (float)sin(rad));
    res.setElement(1, 0,-(float)sin(rad));
    res.setElement(1, 1, (float)cos(rad));

    return res;
}

Matrix2x2 Matrix2x2::createScaleMatrix(const float& dx, const float& dy) {
    Matrix2x2 res;

    res.setElement(0, 0, dx);
    res.setElement(1, 1, dy);

    return res;
}


Matrix2x2::Matrix2x2(void) {
    this->elements_[0][0] = 1.0f;
    this->elements_[0][1] = 0.0f;
    this->elements_[1][0] = 0.0f;
    this->elements_[1][1] = 1.0f;
}

Matrix2x2::Matrix2x2(const Matrix2x2& m) {
    for    (int i = 0; i < MAX_ROWS; i++) {
        for(int j = 0; j < MAX_COLS; j++) {
            this->elements_[i][j] = m.elements_[i][j];
        }
    }
}

Matrix2x2& Matrix2x2::operator =(const Matrix2x2& m){
    for    (int i = 0; i < MAX_ROWS; i++) {
        for(int j = 0; j < MAX_COLS; j++) {
            this->elements_[i][j] = m.elements_[i][j];
        }
    }

    return *this;
}

float Matrix2x2::getElement(const int& row, const int& col) const {
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

Matrix2x2 Matrix2x2::operator + (const Matrix2x2& m) const {    
    Matrix2x2 res;

    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            res.elements_[i][j] = this->elements_[i][j] + m.elements_[i][j];
        }
    }
    return res;
}

Matrix2x2 Matrix2x2::operator - (const Matrix2x2& m) const {
    Matrix2x2 res;

    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            res.elements_[i][j] = this->elements_[i][j] - m.elements_[i][j];
        }
    }
    return res;
}

Matrix2x2& Matrix2x2::operator += (const Matrix2x2& m) {
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            this->elements_[i][j] += m.elements_[i][j];
        }
    }
    return *this;
}

Matrix2x2& Matrix2x2::operator -= (const Matrix2x2& m) {
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            this->elements_[i][j] -= m.elements_[i][j];
        }
    }
    return *this;
}

Matrix2x2& Matrix2x2::operator *= (const float& s) {
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            this->elements_[i][j] *= s;
        }
    }
    return *this;
}

Matrix2x2 Matrix2x2::operator * (const float& s) const {
    Matrix2x2 res;

    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            res.elements_[i][j] = this->elements_[i][j] * s;
        }
    }
    return res;
}

Matrix2x2 Matrix2x2::operator * (const Matrix2x2& m) const {
    Matrix2x2 res;

    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            res.elements_[i][j] = 
                this->elements_[i][0] * m.elements_[0][j] + 
                this->elements_[i][1] * m.elements_[1][j];
        }
    }
    return res;
}

bool Matrix2x2::operator == (const Matrix2x2& m) const {
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            if (this->elements_[i][j] != m.elements_[i][j]) return false;
        }
    }

    return true;
}

Matrix2x2 Matrix2x2::transposition(void) const {
    Matrix2x2 res;

    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            res.elements_[i][j] = this->elements_[j][i];
        }
    }
    return res;
}

float Matrix2x2::determinant(void) const {
    return(
        this->elements_[0][0] * this->elements_[1][1] - 
        this->elements_[1][0] * this->elements_[0][1]
    );
}

Matrix2x2 Matrix2x2::inverse(void) const {
    Matrix2x2 res;
    float det = this->determinant();

    if (fabs(det) < MIN_INCREMENT) {
        throw "can't invert the matrix that has a determinant of 0.";
    }

    res.elements_[0][0] =  this->elements_[1][1] / det;
    res.elements_[0][1] = -this->elements_[0][1] / det;
    res.elements_[1][0] = -this->elements_[1][0] / det;
    res.elements_[1][1] =  this->elements_[0][0] / det;

    return res;
}
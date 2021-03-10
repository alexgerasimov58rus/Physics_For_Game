
#include "Matrix3x3.hpp"
#include <math.h>

#define MAX_ROWS 3
#define MAX_COLS 3
#define MIN_INCREMENT 1e-6

using namespace obj_tools;

Matrix3x3 OBJ_TOOLS_EXPORT obj_tools::operator * (const float& s, const Matrix3x3& m) {
    Matrix3x3 res;

    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            res.elements_[i][j] = s * m.elements_[i][j];
        }
    }
    return res;
}

Matrix3x3::Matrix3x3(void) {
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            if (i == j) {
                this->elements_[i][j] = 1.0f;
            }else {
                this->elements_[i][j] = 0.0f;
            }
        }
    }
}

Matrix3x3::Matrix3x3(const Matrix3x3& m) {
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            this->elements_[i][j] = m.elements_[i][j];
        }
    }
}

Matrix3x3& Matrix3x3::operator =(const Matrix3x3& m) {
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            this->elements_[i][j] = m.elements_[i][j];
        }
    }

    return *this;
}

float Matrix3x3::getElement(const int& row, const int& col) const {
    int r = (row >= MAX_ROWS) ? MAX_ROWS - 1 : row;
    int c = (col >= MAX_COLS) ? MAX_COLS - 1 : col;

    r = (r < 0) ? 0 : r;
    c = (c < 0) ? 0 : c;

    return this->elements_[r][c];
}

void Matrix3x3::setElement(const int& row, const int& col, const float& value) {
    int r = (row >= MAX_ROWS) ? MAX_ROWS - 1 : row;
    int c = (col >= MAX_COLS) ? MAX_COLS - 1 : col;

    r = (r < 0) ? 0 : r;
    c = (c < 0) ? 0 : c;

    this->elements_[r][c] = value;
}

Matrix3x3 Matrix3x3::operator + (const Matrix3x3& m) const {
    Matrix3x3 res;

    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            res.elements_[i][j] = this->elements_[i][j] + m.elements_[i][j];
        }
    }
    return res;
}

Matrix3x3 Matrix3x3::operator - (const Matrix3x3& m) const {
    Matrix3x3 res;

    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            res.elements_[i][j] = this->elements_[i][j] - m.elements_[i][j];
        }
    }
    return res;
}

Matrix3x3& Matrix3x3::operator += (const Matrix3x3& m) {
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            this->elements_[i][j] += m.elements_[i][j];
        }
    }
    return *this;
}

Matrix3x3& Matrix3x3::operator -= (const Matrix3x3& m) {
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            this->elements_[i][j] -= m.elements_[i][j];
        }
    }
    return *this;
}

Matrix3x3 Matrix3x3::operator *= (const float& s)
{
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            this->elements_[i][j] *= s;
        }
    }
    return *this;
}

Matrix3x3 Matrix3x3::operator * (const float& s) const {
    Matrix3x3 res;

    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            res.elements_[i][j] = this->elements_[i][j] * s;
        }
    }
    return res;
}

Matrix3x3 Matrix3x3::operator * (const Matrix3x3& m) const {
    Matrix3x3 res;

    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            res.elements_[i][j] =
                this->elements_[i][0] * m.elements_[0][j] +
                this->elements_[i][1] * m.elements_[1][j] +
                this->elements_[i][2] * m.elements_[2][j];
        }
    }
    return res;
}

bool Matrix3x3::operator == (const Matrix3x3& m) const {
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            if (this->elements_[i][j] != m.elements_[i][j]) return false;
        }
    }

    return true;
}

Matrix3x3 Matrix3x3::transposition(void) const {
    Matrix3x3 res;

    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            res.elements_[i][j] = this->elements_[j][i];
        }
    }
    return res;
}

float Matrix3x3::determinant(void) const {
    return(
        this->elements_[0][0] * this->elements_[1][1] * this->elements_[2][2] -
        this->elements_[0][0] * this->elements_[2][1] * this->elements_[1][2] +
        this->elements_[1][0] * this->elements_[2][1] * this->elements_[0][2] -
        this->elements_[1][0] * this->elements_[0][1] * this->elements_[2][2] +
        this->elements_[2][0] * this->elements_[0][1] * this->elements_[1][2] -
        this->elements_[2][0] * this->elements_[1][1] * this->elements_[0][2]
    );
}

Matrix3x3 Matrix3x3::inverse(void) const {
    Matrix3x3 res;
    float det = this->determinant();

    if (fabs(det) < MIN_INCREMENT) {
        throw "can't invert the matrix that has a determinant of 0.";
    }

    res.elements_[0][0] = (this->elements_[1][1] * this->elements_[2][2] - this->elements_[1][2] * this->elements_[2][1]) / det;
    res.elements_[0][1] = (this->elements_[0][2] * this->elements_[2][1] - this->elements_[0][1] * this->elements_[2][2]) / det;
    res.elements_[0][2] = (this->elements_[0][1] * this->elements_[1][2] - this->elements_[1][1] * this->elements_[0][2]) / det;
    res.elements_[1][0] = (this->elements_[1][2] * this->elements_[2][0] - this->elements_[1][0] * this->elements_[2][2]) / det;
    res.elements_[1][1] = (this->elements_[0][0] * this->elements_[2][2] - this->elements_[0][2] * this->elements_[2][0]) / det;
    res.elements_[1][2] = (this->elements_[0][2] * this->elements_[1][0] - this->elements_[0][0] * this->elements_[1][2]) / det;
    res.elements_[2][0] = (this->elements_[1][0] * this->elements_[2][1] - this->elements_[1][1] * this->elements_[2][0]) / det;
    res.elements_[2][1] = (this->elements_[0][1] * this->elements_[2][0] - this->elements_[0][0] * this->elements_[2][1]) / det;
    res.elements_[2][2] = (this->elements_[0][0] * this->elements_[1][1] - this->elements_[0][1] * this->elements_[1][0]) / det;

    return res;
}
#pragma once

#include "balboa.h"
#include "vector.h"

/// Column-major matrix
template <typename T>
struct TMatrix3x3 {
    TMatrix3x3() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                data[i][j] = T(0);
            }
        }
    }

    template <typename T2>
    TMatrix3x3(const T2 *arr) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                data[i][j] = (T)arr[i * 3 + j];
            }
        }
    }

    template <typename T2>
    TMatrix3x3(const TMatrix3x3<T2> &m) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                data[i][j] = T(m.data[i][j]);
            }
        }
    }

    template <typename T2>
    TMatrix3x3(T2 v00, T2 v01, T2 v02, 
               T2 v10, T2 v11, T2 v12, 
               T2 v20, T2 v21, T2 v22) {
        this->operator()(0, 0) = (T)v00;
        this->operator()(0, 1) = (T)v01;
        this->operator()(0, 2) = (T)v02;
        this->operator()(1, 0) = (T)v10;
        this->operator()(1, 1) = (T)v11;
        this->operator()(1, 2) = (T)v12;
        this->operator()(2, 0) = (T)v20;
        this->operator()(2, 1) = (T)v21;
        this->operator()(2, 2) = (T)v22;
    }

    const T& operator()(int i, int j) const {
        // Column major!
        return data[j][i];
    }

    T& operator()(int i, int j) {
        // Column major!
        return data[j][i];
    }

    static TMatrix3x3<T> identity() {
        TMatrix3x3<T> m(1, 0, 0,
                        0, 1, 0,
                        0, 0, 1);
        return m;
    }

    T* ptr() {
        return &data[0][0];
    }

    const T* ptr() const {
        return &data[0][0];
    }

    T data[3][3];
};

using Matrix3x3 = TMatrix3x3<Real>;
using Matrix3x3f = TMatrix3x3<float>;

template <typename T>
TMatrix3x3<T> inverse(const TMatrix3x3<T> &m) {
    // https://stackoverflow.com/questions/983999/simple-3x3-matrix-inverse-code-c
    TMatrix3x3<T> inv;

    Real det = m(0, 0) * (m(1, 1) * m(2, 2) - m(2, 1) * m(1, 2)) -
               m(0, 1) * (m(1, 0) * m(2, 2) - m(1, 2) * m(2, 0)) +
               m(0, 2) * (m(1, 0) * m(2, 1) - m(1, 1) * m(2, 0));

    if (det == 0) {
        return TMatrix3x3<T>{};
    }

    Real invdet = 1 / det;

    inv(0, 0) = (m(1, 1) * m(2, 2) - m(2, 1) * m(1, 2)) * invdet;
    inv(0, 1) = (m(0, 2) * m(2, 1) - m(0, 1) * m(2, 2)) * invdet;
    inv(0, 2) = (m(0, 1) * m(1, 2) - m(0, 2) * m(1, 1)) * invdet;
    inv(1, 0) = (m(1, 2) * m(2, 0) - m(1, 0) * m(2, 2)) * invdet;
    inv(1, 1) = (m(0, 0) * m(2, 2) - m(0, 2) * m(2, 0)) * invdet;
    inv(1, 2) = (m(1, 0) * m(0, 2) - m(0, 0) * m(1, 2)) * invdet;
    inv(2, 0) = (m(1, 0) * m(2, 1) - m(2, 0) * m(1, 1)) * invdet;
    inv(2, 1) = (m(2, 0) * m(0, 1) - m(0, 0) * m(2, 1)) * invdet;
    inv(2, 2) = (m(0, 0) * m(1, 1) - m(1, 0) * m(0, 1)) * invdet;

    return inv;
}

template <typename T>
inline TMatrix3x3<T> operator*(const TMatrix3x3<T> &m0, const TMatrix3x3<T> &m1) {
    TMatrix3x3<T> ret;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            ret(i, j) = T(0);
            for (int k = 0; k < 3; k++) {
                ret(i, j) += m0(i, k) * m1(k, j);
            }
        }
    }
    return ret;
}

template <typename T>
inline TVector3<T> operator*(const TMatrix3x3<T> &m, const TVector3<T> &v) {
    TVector3<T> ret;
    for (int i = 0; i < 3; i++) {
        ret[i] = T(0);
        for (int j = 0; j < 3; j++) {
            ret[i] += m(i, j) * v[j];
        }
    }
    return ret;
}

template <typename T>
inline std::ostream& operator<<(std::ostream &os, const TMatrix3x3<T> &m) {
    return os << "[[" << m(0, 0) << ", " << m(0, 1) << ", " << m(0, 2) << "]," << std::endl <<
                  "[" << m(1, 0) << ", " << m(1, 1) << ", " << m(1, 2) << "]," << std::endl <<
                  "[" << m(2, 0) << ", " << m(2, 1) << ", " << m(2, 2) << "]]" << std::endl;
}


/// Column-major matrix
template <typename T>
struct TMatrix4x4 {
    TMatrix4x4() {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                data[i][j] = T(0);
            }
        }
    }

    template <typename T2>
    TMatrix4x4(const T2 *arr) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                data[i][j] = (T)arr[i * 4 + j];
            }
        }
    }

    template <typename T2>
    TMatrix4x4(const TMatrix4x4<T2> &m) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                data[i][j] = T(m.data[i][j]);
            }
        }
    }

    template <typename T2>
    TMatrix4x4(T2 v00, T2 v01, T2 v02, T2 v03,
               T2 v10, T2 v11, T2 v12, T2 v13,
               T2 v20, T2 v21, T2 v22, T2 v23,
               T2 v30, T2 v31, T2 v32, T2 v33) {
        this->operator()(0, 0) = (T)v00;
        this->operator()(0, 1) = (T)v01;
        this->operator()(0, 2) = (T)v02;
        this->operator()(0, 3) = (T)v03;
        this->operator()(1, 0) = (T)v10;
        this->operator()(1, 1) = (T)v11;
        this->operator()(1, 2) = (T)v12;
        this->operator()(1, 3) = (T)v13;
        this->operator()(2, 0) = (T)v20;
        this->operator()(2, 1) = (T)v21;
        this->operator()(2, 2) = (T)v22;
        this->operator()(2, 3) = (T)v23;
        this->operator()(3, 0) = (T)v30;
        this->operator()(3, 1) = (T)v31;
        this->operator()(3, 2) = (T)v32;
        this->operator()(3, 3) = (T)v33;
    }

    const T& operator()(int i, int j) const {
        // Column major!
        return data[j][i];
    }

    T& operator()(int i, int j) {
        // Column major!
        return data[j][i];
    }

    static TMatrix4x4<T> identity() {
        TMatrix4x4<T> m(1, 0, 0, 0,
                        0, 1, 0, 0,
                        0, 0, 1, 0,
                        0, 0, 0, 1);
        return m;
    }

    T* ptr() {
        return &data[0][0];
    }

    const T* ptr() const {
        return &data[0][0];
    }

    T data[4][4];
};

using Matrix4x4 = TMatrix4x4<Real>;
using Matrix4x4f = TMatrix4x4<float>;

template <typename T>
TMatrix4x4<T> inverse(const TMatrix4x4<T> &m) {
    // https://stackoverflow.com/questions/1148309/inverting-a-4x4-matrix
    TMatrix4x4<T> inv;

    inv(0, 0) = m(1, 1) * m(2, 2) * m(3, 3) -
                m(1, 1) * m(2, 3) * m(3, 2) -
                m(2, 1) * m(1, 2) * m(3, 3) +
                m(2, 1) * m(1, 3) * m(3, 2) +
                m(3, 1) * m(1, 2) * m(2, 3) -
                m(3, 1) * m(1, 3) * m(2, 2);

    inv(1, 0) = -m(1, 0) * m(2, 2) * m(3, 3) +
                 m(1, 0) * m(2, 3) * m(3, 2) +
                 m(2, 0) * m(1, 2) * m(3, 3) -
                 m(2, 0) * m(1, 3) * m(3, 2) -
                 m(3, 0) * m(1, 2) * m(2, 3) +
                 m(3, 0) * m(1, 3) * m(2, 2);

    inv(2, 0) = m(1, 0) * m(2, 1) * m(3, 3) -
                m(1, 0) * m(2, 3) * m(3, 1) -
                m(2, 0) * m(1, 1) * m(3, 3) +
                m(2, 0) * m(1, 3) * m(3, 1) +
                m(3, 0) * m(1, 1) * m(2, 3) -
                m(3, 0) * m(1, 3) * m(2, 1);

    inv(3, 0) = -m(1, 0) * m(2, 1) * m(3, 2) +
                 m(1, 0) * m(2, 2) * m(3, 1) +
                 m(2, 0) * m(1, 1) * m(3, 2) -
                 m(2, 0) * m(1, 2) * m(3, 1) -
                 m(3, 0) * m(1, 1) * m(2, 2) +
                 m(3, 0) * m(1, 2) * m(2, 1);

    inv(0, 1) = -m(0, 1) * m(2, 2) * m(3, 3) +
                 m(0, 1) * m(2, 3) * m(3, 2) +
                 m(2, 1) * m(0, 2) * m(3, 3) -
                 m(2, 1) * m(0, 3) * m(3, 2) -
                 m(3, 1) * m(0, 2) * m(2, 3) +
                 m(3, 1) * m(0, 3) * m(2, 2);

    inv(1, 1) = m(0, 0) * m(2, 2) * m(3, 3) -
                m(0, 0) * m(2, 3) * m(3, 2) -
                m(2, 0) * m(0, 2) * m(3, 3) +
                m(2, 0) * m(0, 3) * m(3, 2) +
                m(3, 0) * m(0, 2) * m(2, 3) -
                m(3, 0) * m(0, 3) * m(2, 2);

    inv(2, 1) = -m(0, 0) * m(2, 1) * m(3, 3) +
                 m(0, 0) * m(2, 3) * m(3, 1) +
                 m(2, 0) * m(0, 1) * m(3, 3) -
                 m(2, 0) * m(0, 3) * m(3, 1) -
                 m(3, 0) * m(0, 1) * m(2, 3) +
                 m(3, 0) * m(0, 3) * m(2, 1);

    inv(3, 1) = m(0, 0) * m(2, 1) * m(3, 2) -
                m(0, 0) * m(2, 2) * m(3, 1) -
                m(2, 0) * m(0, 1) * m(3, 2) +
                m(2, 0) * m(0, 2) * m(3, 1) +
                m(3, 0) * m(0, 1) * m(2, 2) -
                m(3, 0) * m(0, 2) * m(2, 1);

    inv(0, 2) = m(0, 1) * m(1, 2) * m(3, 3) -
                m(0, 1) * m(1, 3) * m(3, 2) -
                m(1, 1) * m(0, 2) * m(3, 3) +
                m(1, 1) * m(0, 3) * m(3, 2) +
                m(3, 1) * m(0, 2) * m(1, 3) -
                m(3, 1) * m(0, 3) * m(1, 2);

    inv(1, 2) = -m(0, 0) * m(1, 2) * m(3, 3) +
                 m(0, 0) * m(1, 3) * m(3, 2) +
                 m(1, 0) * m(0, 2) * m(3, 3) -
                 m(1, 0) * m(0, 3) * m(3, 2) -
                 m(3, 0) * m(0, 2) * m(1, 3) +
                 m(3, 0) * m(0, 3) * m(1, 2);

    inv(2, 2) = m(0, 0) * m(1, 1) * m(3, 3) -
                m(0, 0) * m(1, 3) * m(3, 1) -
                m(1, 0) * m(0, 1) * m(3, 3) +
                m(1, 0) * m(0, 3) * m(3, 1) +
                m(3, 0) * m(0, 1) * m(1, 3) -
                m(3, 0) * m(0, 3) * m(1, 1);

    inv(3, 2) = -m(0, 0) * m(1, 1) * m(3, 2) +
                 m(0, 0) * m(1, 2) * m(3, 1) +
                 m(1, 0) * m(0, 1) * m(3, 2) -
                 m(1, 0) * m(0, 2) * m(3, 1) -
                 m(3, 0) * m(0, 1) * m(1, 2) +
                 m(3, 0) * m(0, 2) * m(1, 1);

    inv(0, 3) = -m(0, 1) * m(1, 2) * m(2, 3) +
                 m(0, 1) * m(1, 3) * m(2, 2) +
                 m(1, 1) * m(0, 2) * m(2, 3) -
                 m(1, 1) * m(0, 3) * m(2, 2) -
                 m(2, 1) * m(0, 2) * m(1, 3) +
                 m(2, 1) * m(0, 3) * m(1, 2);

    inv(1, 3) = m(0, 0) * m(1, 2) * m(2, 3) -
                m(0, 0) * m(1, 3) * m(2, 2) -
                m(1, 0) * m(0, 2) * m(2, 3) +
                m(1, 0) * m(0, 3) * m(2, 2) +
                m(2, 0) * m(0, 2) * m(1, 3) -
                m(2, 0) * m(0, 3) * m(1, 2);

    inv(2, 3) = -m(0, 0) * m(1, 1) * m(2, 3) +
                 m(0, 0) * m(1, 3) * m(2, 1) +
                 m(1, 0) * m(0, 1) * m(2, 3) -
                 m(1, 0) * m(0, 3) * m(2, 1) -
                 m(2, 0) * m(0, 1) * m(1, 3) +
                 m(2, 0) * m(0, 3) * m(1, 1);

    inv(3, 3) = m(0, 0) * m(1, 1) * m(2, 2) -
                m(0, 0) * m(1, 2) * m(2, 1) -
                m(1, 0) * m(0, 1) * m(2, 2) +
                m(1, 0) * m(0, 2) * m(2, 1) +
                m(2, 0) * m(0, 1) * m(1, 2) -
                m(2, 0) * m(0, 2) * m(1, 1);

    auto det = m(0, 0) * inv(0, 0) +
               m(0, 1) * inv(1, 0) +
               m(0, 2) * inv(2, 0) +
               m(0, 3) * inv(3, 0);

    if (det == 0) {
        return TMatrix4x4<T>{};
    }

    auto inv_det = 1.0 / det;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            inv(i, j) *= inv_det;
        }
    }

    return inv;
}

template <typename T>
inline TMatrix4x4<T> operator*(const TMatrix4x4<T> &m0, const TMatrix4x4<T> &m1) {
    TMatrix4x4<T> ret;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            ret(i, j) = T(0);
            for (int k = 0; k < 4; k++) {
                ret(i, j) += m0(i, k) * m1(k, j);
            }
        }
    }
    return ret;
}

template <typename T>
inline TVector4<T> operator*(const TMatrix4x4<T> &m, const TVector4<T> &v) {
    TVector4<T> ret;
    for (int i = 0; i < 4; i++) {
        ret[i] = T(0);
        for (int j = 0; j < 4; j++) {
            ret[i] += m(i, j) * v[j];
        }
    }
    return ret;
}

template <typename T>
inline std::ostream& operator<<(std::ostream &os, const TMatrix4x4<T> &m) {
    return os << "[[" << m(0, 0) << ", " << m(0, 1) << ", " << m(0, 2) << ", " << m(0, 3) << "]," << std::endl <<
                  "[" << m(1, 0) << ", " << m(1, 1) << ", " << m(1, 2) << ", " << m(1, 3) << "]," << std::endl <<
                  "[" << m(2, 0) << ", " << m(2, 1) << ", " << m(2, 2) << ", " << m(2, 3) << "]," << std::endl <<
                  "[" << m(3, 0) << ", " << m(3, 1) << ", " << m(3, 2) << ", " << m(3, 3) << "]]" << std::endl;
}

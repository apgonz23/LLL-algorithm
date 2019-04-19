// Vector stucture
#ifndef __VEC_H__
#define __VEC_H__

#include <cmath>
#include <vector>
#include <cassert>
#include <iostream>

template<class T> struct vec;
template<class T> T dot(const vec<T>& u, const vec<T>& v);

template<class T>
struct vec {
    int size;
    std::vector<T> v;
   
    vec() {
        size = 0;
    }

    vec(int n) {
        v.resize(n, 0);
        size = n;
    }
    
    vec(std::vector<T> list) { 
        v = list;
        size = v.size();
    }

    void fill(T value) {
        for (int i = 0; i < size; i++) v[i] = value;
    }

    // vector operations
    vec& operator += (const vec& x) {
        for (int i = 0; i < size; i++) v[i] += x.v[i];
        return *this;
    }
    
    vec& operator -= (const vec& x) {
        for (int i = 0; i < size; i++) v[i] -= x.v[i];
        return *this;
    }

    vec& operator *= (const vec& x) {
        for (int i = 0; i < size; i++) v[i] *= x.v[i];
        return *this;
    }

    vec& operator /= (const vec& x) {
        for (int i = 0; i < size; i++) v[i] /= x.v[i];
        return *this;
    }

    // scalar operations
    vec& operator *= (const T& c) {
        for (int i = 0; i < size; i++) v[i] *= c;
        return *this;
    }
    
    vec& operator /= (const T& c) {
        for (int i = 0; i < size; i++) v[i] /= c;
        return *this;
    }
    
    // negative sign
    vec operator - () const {
        vec r(size);
        for (int i = 0; i < size; i++) r[i] = -v[i];
        return r;
    }

    vec operator + (const vec& x) const {
        vec r(size);
        for (int i = 0; i < size; i++) r[i] = v[i] + x.v[i];
        return r;
    }
    
    vec operator - (const vec& x) const {
        vec r(size);
        for (int i = 0; i < size; i++) r[i] = v[i] - x.v[i];
        return r;
    }

    vec operator * (const vec& x) const {
        vec r(size);
        for (int i = 0; i < size; i++) r[i] = v[i] * x.v[i];
        return r;
    }

    vec operator / (const vec& x) const {
        vec r(size);
        for (int i = 0; i < size; i++) r[i] = v[i] / x.v[i];
        return r;
    }

    vec operator * (const T& c) const {
        vec r(size);
        for (int i = 0; i < size; i++) r[i] = v[i] * c;
        return r;
    }

    vec operator / (const T& c) const {
        vec r(size);
        for (int i = 0; i < size; i++) r[i] = v[i] / c;
        return r;
    }

    const T& operator[] (int i) const {
        return v[i];
    }

    T& operator[] (int i) {
        return v[i];
    }

    T magnitude_squared() const {
        return dot(*this, *this);
    }

    T magnitude() const {
        return sqrt(magnitude_squared());
    }

    vec normalize() const {
        T mag = magnitude();
        if (mag) return *this / mag;
        vec r(size);
        r[0] = 1;
        return r;
    }

};

template<class T>
T dot(const vec<T>& u, const vec<T>& v) {
    assert(u.size == v.size);
    T p = 0;
    for (int i = 0; i < u.size; i++) p += u.v[i] * v.v[i];
    return p;
}

template<class T>
vec<T> operator * (const T& c, const vec<T>& v) {
    return v * c;
}

template<class T>
std::ostream& operator << (std::ostream& out, const vec<T>& u) {
    for (int i = 0; i < u.size; i++) {
        if(i) out << ' ';
        out << u[i];
    }
    return out;
}

//
typedef vec<double> vec_d; 

#endif

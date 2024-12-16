// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
    size_t sz;
    T* pMem;
public:
    TDynamicVector(size_t size = 1) : sz(size)
    {
        if (sz == 0)
            throw out_of_range("Vector size should be greater than zero");
        if (sz > MAX_VECTOR_SIZE) throw ("Массив слишком большого размера");
        pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
    }
    TDynamicVector(T* arr, size_t s) : sz(s)
    {
        assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
        pMem = new T[sz];
        std::copy(arr, arr + sz, pMem);
    }
    TDynamicVector(const TDynamicVector& v)
    {
        sz = v.sz;
        pMem = new T[sz];
        std::copy(v.pMem, v.pMem + sz, pMem); //использовать memcpy нельзя так как T в нашем случае - нетривиальный тип
    }
    TDynamicVector(TDynamicVector&& v) noexcept
    {
        pMem = nullptr;
        swap(*this, v);
    }
    ~TDynamicVector()
    {
        delete[] pMem;
    }
    TDynamicVector& operator=(const TDynamicVector& v)
    {
        if (this == &v) return *this;
        if (sz != v.sz) {
            T* p = new T[v.sz];
            delete[] pMem;
            sz = v.sz;
            pMem = p;
        }
        std::copy(v.pMem, v.pMem + sz, pMem);
        return *this;
    }
    TDynamicVector& operator=(TDynamicVector&& v) noexcept
    {
        swap(*this, v);
        return *this;
    }

    size_t size() const noexcept { return sz; }

    // индексация
    T& operator[](size_t ind)
    {
        if ((ind < this->size()) && (ind >= 0)) return pMem[ind];
        else throw ("Отрицательный индекс или индекс за пределами массива!");
    }
    const T& operator[](size_t ind) const
    {
        if ((ind < this->size()) && (ind >= 0)) return pMem[ind];
        else throw ("Отрицательный индекс или индекс за пределами массива!");
    }
    // индексация с контролем
    T& at(size_t ind)
    {
        if ((ind < this->size()) && (ind >= 0)) return pMem[ind];
    }
    const T& at(size_t ind) const
    {
        if ((ind < this->size()) && (ind >= 0)) return pMem[ind];
    }

    // сравнение
    bool operator==(const TDynamicVector& v) const noexcept
    {
        if (pMem == v.pMem) return 1;
        if (this->size() == v.size()) {
            for (size_t i = 0; i < this->size(); i++) { if (pMem[i] != v.pMem[i]) return 0; break; } return 1;
        }
        return 0;
    }
    bool operator!=(const TDynamicVector& v) const noexcept
    {
        return !(*this == v);
    }

    // скалярные операции
    TDynamicVector operator+(T val)
    {
        TDynamicVector tmp(sz);
        for (size_t i = 0; i < sz; i++) {
            tmp.pMem[i] = this->pMem[i] + val;
        }
        return tmp;
    }
    TDynamicVector operator-(T val)
    {
        TDynamicVector tmp(sz);
        for (size_t i = 0; i < sz; i++) {
            tmp.pMem[i] = this->pMem[i] - val;
        }
        return tmp;
    }
    TDynamicVector operator*(T val)
    {
        TDynamicVector tmp(sz);
        for (size_t i = 0; i < sz; i++) {
            tmp.pMem[i] = this->pMem[i] * val;
        }
        return tmp;
    }

    // векторные операции
    TDynamicVector operator+(const TDynamicVector& v)
    {
        if (sz == v.sz) {
            TDynamicVector tmp(sz);
            for (size_t i = 0; i < sz; i++) {
                tmp.pMem[i] = this->pMem[i] + v.pMem[i];
            }
            return tmp;
        }
        else throw ("Вектора должны быть одинакового размера");
    }
    TDynamicVector operator-(const TDynamicVector& v)
    {
        if (sz == v.sz) {
            TDynamicVector tmp(sz);
            for (size_t i = 0; i < sz; i++) {
                tmp.pMem[i] = this->pMem[i] - v.pMem[i];
            }
            return tmp;
        }
        else throw ("Вектора должны быть одинакового размера");
    }
    T operator*(const TDynamicVector& v)
    {
        if (sz == v.sz) {
            TDynamicVector tmp(sz);
            T k{};
            for (size_t i = 0; i < sz; i++) {
                tmp.pMem[i] = this->pMem[i] * v.pMem[i];
                k += tmp.pMem[i];
            }
            return k;
        }
        else throw ("Вектора должны быть одинакового размера");
    }

    friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
    {
        std::swap(lhs.sz, rhs.sz);
        std::swap(lhs.pMem, rhs.pMem);
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            istr >> v.pMem[i]; // требуется оператор>> для типа T
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; i++)
            ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
        return ostr;
    }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
    using TDynamicVector<TDynamicVector<T>>::pMem;
    using TDynamicVector<TDynamicVector<T>>::sz;
public:
    
    TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
    {
        if (s < MAX_MATRIX_SIZE) {
            sz = s;
            for (size_t i = 0; i < sz; i++)
                pMem[i] = TDynamicVector<T>(sz);
        }
        else throw ("Невозможно создать");
    }

    size_t size(){
        return sz;
    }

    using TDynamicVector<TDynamicVector<T>>::operator[];

    // сравнение
    bool operator==(const TDynamicMatrix& m) const noexcept
    {
        return TDynamicVector<TDynamicVector<T>>::operator==(m);
    }

    // матрично-скалярные операции
    TDynamicMatrix<T> operator*(const T& val)
    {
        TDynamicMatrix tmp(sz);
        for (size_t i = 0; i < sz; i++) {
            tmp.pMem[i] = pMem[i] * val;
        }
        return tmp;
    }

    // матрично-векторные операции
    TDynamicMatrix<T> operator*(const TDynamicVector<T>& v)
    {
        TDynamicMatrix tmp(sz);
        for (size_t i = 0; i < sz; i++) {
            tmp.pMem[i] = pMem[i] * v;
        }
        return tmp;
    }

    // матрично-матричные операции
    TDynamicMatrix operator+(const TDynamicMatrix& m)
    {
        if (sz == m.sz) {
            TDynamicMatrix tmp(sz);
            for (size_t i = 0; i < sz; i++) {
                tmp.pMem[i] = pMem[i] + m.pMem[i];
            }
            return tmp;
        }
        else throw ("Матрицы должны быть одинакового размера!");
    }
    TDynamicMatrix operator-(const TDynamicMatrix& m)
    {
        if (sz == m.sz) {
            TDynamicMatrix tmp(sz);
            for (size_t i = 0; i < sz; i++) {
                tmp.pMem[i] = pMem[i] - m.pMem[i];
            }
            return tmp;
        }
        else throw ("Матрицы должны быть одинакового размера!");
    }
    TDynamicMatrix operator*(const TDynamicMatrix& m)
    {
        TDynamicMatrix tmp(sz);
        for (size_t i = 0; i < sz; i++) {
            for (size_t j = 0; j < sz; j++) {
                for (size_t k = 0; k < sz; k++) {
                    tmp.pMem[i][j] += pMem[i][k] * m.pMem[k][j];
                }
            }
        }
        return tmp;
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicMatrix& v)
    {
        for (size_t i = 0; i < v.sz; i++) {
            for (size_t j = 0; j < v.sz; j++) {
                istr >> v[i][j];
            }
        }
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
    {
        for (size_t i = 0; i < v.sz; i++) {
            if (i >= 1) { ostr << endl; }
            for (size_t j = 0; j < v.sz; j++) {
                ostr << v[i][j] << "\t";
            }
        }
        return ostr;
    }
};

#endif
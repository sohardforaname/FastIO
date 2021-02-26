#define _CRT_SECURE_NO_WARNINGS
#pragma once

//#include "ReadIOBase.hpp"
#include "ReadIOSSE.hpp"
#include "WriteIOBase.hpp"
#include <vector>
#include <tuple>

using namespace std;

typedef long long ll;

class ReadIO {

private:
    ReadIOBase_SSE rio;
    //ReadIOBase rio;
    size_t readElement;

public:
    //input basic type
    template <class T>
    inline int operator()(T& x)
    {
        return rio._read(x);
    }

private:
    template <class T>
    inline int getarray(T& arr, const size_t beg, const size_t end)
    {
        int rtv = -1;
        readElement = 0;
        for (size_t i = beg; i < end && rtv; ++i, ++readElement)
            rtv = (*this)(arr[i]);
        return rtv;
    }

public:
    template <class T>
    static tuple<vector<T>&, size_t> make(
        vector<T>& vec, size_t size)
    {
        return make_tuple(ref(vec), size);
    }
    template <class T>
    inline int operator()(tuple<vector<T>&, size_t> tp)
    {
        auto& vec = get<0>(tp);
        auto len = get<1>(tp);

        vec.resize(len);
        return getarray(vec, 0, len);
    }

    //input a series of numbers and store them in an array
    template <class T>
    static tuple<T*, size_t, size_t> make(
        T* arr, size_t beg, size_t end)
    {
        return make_tuple(arr, beg, end);
    }
    template <class T>
    inline int operator()(tuple<T*, size_t, size_t> tp)
    {
        return getarray(get<0>(tp), get<1>(tp), get<2>(tp));
    }

    //input function that receives variable values
    template <class T, class... Ts>
    inline int operator()(T&& x, Ts&&... y)
    {
        return (*this)(forward<T>(x)) + (*this)(y...);
    }

    inline size_t GetReadElement() const
    {
        return readElement;
    }

    inline pair<int, int> GetReadStatus() const
    {
        return rio.GetStatus();
    }

    inline long long GetReadSize() const
    {
        return rio.GetReadSize();
    }
};
class WriteIO {

private:
    WriteIOBase wio;
    size_t w;

public:
    void setw(const size_t w) {
        this->w = w;
    }

public:
    // output a integer
    template <class T>
    void operator()(const T x, const char ch) {
        if (x < 0)
            putchar('-');
        wio._write(x > 0 ? x : -x);
        putchar(ch);
    }

    // output a char
    void operator()(const char x, const char ch) {
        putchar(x);
    }

    // output a float
    void operator()(const double x, const char ch) {
        printf("%.*lf", w, x);
        putchar(ch);
    }

    // output a container
    template <class Iter>
    void operator()(Iter beg, Iter end, const char ch) {
        for (auto it = beg; it != end; ++it)
            (*this)(*it, ch);
        putchar('\n');
    }

    //output a string
    void operator()(const char* s, const char ch, void* plshd) {
        printf("%s%c", s, ch);
    }

    // output an array
    template <class T>
    void operator()(const T* arr, int beg, int end, const char ch) {
        for (auto it = beg; it != end; ++it)
            (*this)(arr[it], ch);
        putchar('\n');
    }

    WriteIO()
        : w(6)
    {
    }

}; //class IO
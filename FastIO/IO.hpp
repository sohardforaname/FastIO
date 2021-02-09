#define _CRT_SECURE_NO_WARNINGS
#pragma once

#include <vector>
#include "type.h"
#include <cstdio>
#include <cstring>
#include <tuple>

using namespace std;

typedef long long ll;

const double pow10minus[] = {
    1e-1, 1e-2, 1e-3, 1e-4, 1e-5, 1e-6, 1e-7, 1e-8, 1e-9, 1e-10,
    1e-11, 1e-12, 1e-13, 1e-14, 1e-15, 1e-16, 1e-17, 1e-18, 1e-19, 1e-20
};

class ReadIOBase {
private:
    static const size_t MAXBUF = 1 << 23;
    char buf[MAXBUF + 1], *fh, *ft;
    bool f;
    int iserr;

    inline void readbuf()
    {
        fh = buf;
        *fh = 0;
        ft = fh + fread(buf, 1, MAXBUF, stdin);
        if (ft == fh)
            iserr = ferror(stdin);
    }

    inline char gc()
    {
        return *fh++;
    }

    inline char seekch()
    {
        if (*fh)
            return *fh;
        readbuf();
        return *fh;
    }

    inline void skipspace()
    {
        while (!isgraph(seekch()))
            gc();
    }

public:
    template <class T>
    inline int _read(T& x)
    {
        f = 1;
        skipspace();
        char c = seekch();
        if (c == '+' || c == '-') {
            f = (c == '+');
            c = gc();
            if (!isdigit(seekch()))
                return 0;
            x = 0;
        } 
        else if (isdigit(c))
            x = gc() - '0';
        else
            return 0;
        while (isdigit(seekch()))
            x = (x << 3) + (x << 1) + gc() - '0';
        if (!f)
            x = ~x + 1;
        return 1;
    }

    inline int _read(double& x)
    {
        ll inte;
        if (!_read(inte))
            return 0;
        x = inte;
        if (seekch() != '.')
            return 1;
        gc();
        if (!isdigit(seekch()))
            return 0;
        const double* p = pow10minus;
        while (isdigit(seekch()))
            f ? x += *(p++) * (gc() - '0') : x -= *(p++) * (gc() - '0');
        return 1;
    }

#define cpy(a, b, c)            \
    memcpy((a), (b), (c) - (b));\
    (a) += (c) - (b);

    inline int _read(char* s)
    {
        skipspace();
        char* ptr = fh;
        while (isgraph(seekch())) {
            gc();
            if (*fh)
                continue;
            cpy(s, ptr, fh)
            readbuf();
            ptr = fh;
        };
        if (fh != ptr) {
            cpy(s, ptr, fh);
        }
        *s = 0;
        return 1;
    }
#undef cpy(a,b,c)

    inline int _read(char& ch)
    {
        ch = gc();
        return 1;
    }

    int GetStatus() const
    {
        return iserr;
    }

    ReadIOBase()
        : ft(buf)
        , fh(buf)
    {
        buf[0] = buf[MAXBUF] = 0;
    }
};
class WriteIOBase {

public:
    template <class T>
    constexpr void _write(const T& x)
    {
        if (x > 9)
            _write(x / 10);
        putchar(x % 10 + '0');
    }
};

class IO : public ReadIOBase, public WriteIOBase {

private:
    size_t readElement;

public:
    //input basic type
    template <class T>
    inline int operator()(T& x)
    {
        return _read(x);
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
    inline int operator()(T& x, Ts&... y)
    {
        return (*this)(x) + (*this)(y...);
    }

    size_t GetReadElement() const
    {
        return readElement;
    }

    size_t IsEofOrError() const
    {
        return GetStatus();
    }

private:
    size_t w;

public:
    void setw(const size_t w)
    {
        this->w = w;
    }

public:
    // output a integer
    template <class T>
    void operator()(const T x, const char ch)
    {
        if (x < 0)
            putchar('-');
        _write(x > 0 ? x : -x);
        putchar(ch);
    }

    // output a char
    void operator()(const char x, const char ch)
    {
        putchar(x);
    }

    // output a float
    void operator()(const double x, const char ch)
    {
        printf("%.*lf", w, x);
        putchar(ch);
    }

    // output a container
    template <class Iter>
    void operator()(Iter beg, Iter end, const char ch)
    {
        for (auto it = beg; it != end; ++it)
            (*this)(*it, ch);
        putchar('\n');
    }

    //output a string
    void operator()(const char* s, const char ch, void* plshd)
    {
        printf("%s%c", s, ch);
    }

    // output an array
    template <class T>
    void operator()(const T* arr, int beg, int end, const char ch)
    {
        for (auto it = beg; it != end; ++it)
            (*this)(arr[it], ch);
        putchar('\n');
    }

    IO()
        : w(6)
    {
    }

}; //class IO
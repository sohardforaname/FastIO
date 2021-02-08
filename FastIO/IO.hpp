#define _CRT_SECURE_NO_WARNINGS
#pragma once

#include <vector>
#include <cctype>
#include <cstdio>
#include <tuple>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef pair<int, int> pii;
typedef pair<int, ll> pil;
typedef pair<ll, int> pli;
typedef pair<ll, ll> pll;
typedef vector<pii> vpii;

class ReadIOBase {
private:
    static const size_t MAXBUF = 1 << 23;
    char buf[MAXBUF], *fh, *ft;
    int f, iserr;
    inline void checkbuf()
    {
        if (fh == ft) {
            fh = buf;
            *fh = 0;
            ft = fh + fread(buf, 1, MAXBUF, stdin);
            iserr = ferror(stdin);
        }
    }

    inline char gc()
    {
        checkbuf();
        return *fh++;
    }

    inline char seekch()
    {
        checkbuf();
        return *fh;
    }

    void skipspace()
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
            f = (c == '+' ? 1 : -1);
            c = gc();
            if (!isdigit(seekch()))
                return 0;
            x = 0;
        } else if (isdigit(c))
            x = gc() - '0';
        else
            return 0;
        while (isdigit(seekch()))
            x = x * 10 + gc() - '0';
        x *= f;
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
        double p = 0.1;
        while (isdigit(seekch()))
            x += p * (gc() - '0') * f, p *= 0.1;
        return 1;
    }

    inline int _read(char* s)
    {
        skipspace();
        while (isgraph(seekch()))
            *(s++) = gc();
        *s = 0;
        return 1;
    }

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
        : ft(nullptr)
        , fh(nullptr)
    {
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
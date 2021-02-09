#define _CRT_SECURE_NO_WARNINGS
#pragma once

#include "type.h"
#include <cstdio>
#include <cstring>
#include <nmmintrin.h>

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
        } else if (isdigit(c))
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

#define cpy(a, b, c)             \
    memcpy((a), (b), (c) - (b)); \
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
#undef cpy(a, b, c)

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
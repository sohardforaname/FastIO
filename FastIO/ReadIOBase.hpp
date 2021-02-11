#pragma once

#include <cstdio>
#include <cstring>
#include "type.h"

const double pow10Minus[] = {
    1,
    0.1,
    0.01,
    0.001,
    0.0001,
    0.00001,
    0.000001,
    0.0000001,
    0.00000001,
    0.000000001,
    0.0000000001,
    0.00000000001,
    0.000000000001,
    0.0000000000001,
    0.00000000000001,
    0.000000000000001,
    0.0000000000000001,
    0.00000000000000001
};

const double minusPow10Minus[] = {
    -1,
    -0.1,
    -0.01,
    -0.001,
    -0.0001,
    -0.00001,
    -0.000001,
    -0.0000001,
    -0.00000001,
    -0.000000001,
    -0.0000000001,
    -0.00000000001,
    -0.000000000001,
    -0.0000000000001,
    -0.00000000000001,
    -0.000000000000001,
    -0.0000000000000001,
    -0.00000000000000001
};

class ReadIOBase {
private:
    static const size_t MAXBUF = 1 << 23;
    char buf[MAXBUF + 1], *fh, *ft;
    int f, iserr;
    long long readSize;

    inline void ReadBuf()
    {
        fh = buf;
        ft = fh + fread(buf, 1, MAXBUF, stdin);
        readSize += ft - fh;
        *ft = 0;
        if (ft == fh)
            iserr = ferror(stdin);
    }

    inline int Gc()
    {
        return *fh++;
    }

    inline int SeekCh()
    {
        if (*fh)
            return *fh;
        ReadBuf();
        return *fh;
    }

    inline void SkipSpace()
    {
        while (!IsGraph(SeekCh()))
            Gc();
    }

public:
    template <class T>
    inline int _read(T& x)
    {
        SkipSpace();
        char c = SeekCh();
        if (IsDigit(c)) {
            f = 1;
        } else if (c == '-' || c == '+') {
            f = c == '-' ? -1 : 1;
            c = Gc();
            if (!IsDigit(SeekCh()))
                return 0;
        } else
            return 0;
        x = 0;
        while (IsDigit(SeekCh()))
            x = (x << 3) + (x << 1) + (Gc() ^ '0');
        if (f & 0x80000000)
            x = ~x + 1;
        return 1;
    }

    inline int _read(double& x)
    {
        SkipSpace();
        char c = SeekCh();
        if (IsDigit(c)) {
            f = 1;
        } else if (c == '-' || c == '+') {
            f = c == '-' ? -1 : 1;
            c = Gc();
            if (!IsDigit(SeekCh()))
                return 0;
        } else
            return 0;
        x = 0;
        while (IsDigit(SeekCh()))
            x = x * 10.0 + (Gc() ^ '0');
        if ((SeekCh() ^ '.'))
            return 1;
        Gc();
        if (!IsDigit(SeekCh()))
            return 0;
        const double* p = (f == 1 ? pow10Minus : minusPow10Minus);
        while (IsDigit(SeekCh())) {
            x = x * 10.0 + (Gc() ^ '0');
            ++p;
        }
        x *= *p;
        return 1;
    }

#define cpy(a, b, c)             \
    memcpy((a), (b), (c) - (b)); \
    (a) += (c) - (b);

    inline int _read(char* s)
    {
        SkipSpace();
        char* ptr = fh;
        while (IsGraph(SeekCh())) {
            Gc();
            if (*fh)
                continue;
            cpy(s, ptr, fh)
                ReadBuf();
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
        ch = SeekCh();
        Gc();
        return 1;
    }

    inline int GetStatus() const
    {
        return iserr;
    }

    inline long long GetReadSize() const 
    {
        return readSize;
    }

    ReadIOBase()
        : ft(buf)
        , fh(buf)
        , f(1)
        , readSize(0)
    {
        buf[0] = buf[MAXBUF] = 0;
    }
};
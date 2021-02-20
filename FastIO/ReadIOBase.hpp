#pragma once

#include <cstdio>
#include <cstring>
#include <utility>

using namespace std;

static const double pow10Minus[] = {
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
    int f, isok, iserr;
    long long readSize;

    inline void ReadBuf() {
        if (isok) {
            fh = buf;
            ft = fh + fread(buf, 1, MAXBUF, stdin);
            readSize += ft - fh;
            *ft = 0;
            if (ft == fh) {
                iserr = ferror(stdin);
                isok = 0;
            }
        }
    }

    inline bool IsGraph(const int ch) {
        return !(ch < 33 || ch > 126);
    }

    inline bool IsDigit(const int ch) {
        return !(ch > 57 || ch < 48);
    }

    inline int Gc() {
        return *fh++;
    }

    inline int SeekCh() {
        if (*fh)
            return *fh;
        ReadBuf();
        return isok ? *fh : 0;
    }

    inline void SkipSpace() {
        while (!IsGraph(SeekCh()) && isok)
            Gc();
    }

    template<class T>
    inline void StrToLL(T& x) {
        while (IsDigit(SeekCh()))
            x = (x << 3) + (x << 1) + (Gc() ^ '0');
    }

    inline int PreCal() {
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
        return 1;
    }

public:
    template <class T>
    inline int _read(T& x) {
        if (!PreCal())
            return 0;
        x = 0;
        StrToLL(x);
        if (f & 0x80000000)
            x = ~x + 1;
        return 1;
    }

    inline int _read(double& x) {
        if (!PreCal())
            return 0;
        long long tmpl = 0;
        x = 0;
        StrToLL(tmpl);
        if ((SeekCh() ^ '.'))
            return 1;
        Gc();
        if (!IsDigit(SeekCh()))
            return 0;
        const char* ptr = fh;
        StrToLL(tmpl);
        static size_t pos = (fh - ptr + MAXBUF) & (MAXBUF - 1);
        x = tmpl * (f == 1 ? pow10Minus[pos] : minusPow10Minus[pos]);
        return 1;
    }

#define cpy(a, b, c)             \
    memcpy((a), (b), (c) - (b)); \
    (a) += (c) - (b);

    inline int _read(char* s) {
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
        return ptr != fh;
    }
#undef cpy

    inline int _read(char& ch) {
        ch = SeekCh();
        Gc();
        return isok & 1;
    }

    inline pair<int, int> GetStatus() const {
        return std::move(pair<int, int>(isok, iserr));
    }

    inline long long GetReadSize() const  {
        return readSize;
    }

    void reset() {
        ft = buf;
        fh = buf;
        f = 1;
        readSize = 0;
        iserr = 0;
        isok = 1;
        buf[0] = buf[MAXBUF] = 0;
    }

    ReadIOBase() {
        reset();
    }
};
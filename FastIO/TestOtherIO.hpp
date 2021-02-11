#pragma once

#include <cstdio>
#include <cstring>
#include <utility>

using namespace std;

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
    char buf[(1 << 4) + MAXBUF + 1]; // align 16
    char* st; // buffer boundary pointer
    char *fh, *ft; // buffer read pointer
    int isOK, isErr; // tag 
    long long readSize;

    inline void ReadBuf() {
        if (isOk) {
            fh = st;
            ft = fh + fread(fh, 1, MAXBUF, stdin);
            readSize += ft - fh;
            *ft = 0;
            if (ft == fh) {
                isErr = ferror(stdin);
                isOK = 0;
            }
        }
    }

    inline int GetCh() {
        if (fh != ft)
            return *fh++; 
        buf[3] = *(fh - 1);
        ReadBuf();
        return *fh++;
    }

    inline void Undo() {
        --fh;
    }

    inline bool IsGraph(const int ch) {
        return !(ch < 33 || ch > 126);
    }

    inline bool IsDigit(const int ch) {
        return !(ch > 57 || ch < 48);
    }

    inline void SkipSpace() {
        while (!IsGraph(GetCh()) && isOK)
            ;
        Undo();
    }

    template <class T>
    inline void StrToLL(T& x)
    {
        while (IsDigit(SeekCh()))
            x = (x << 3) + (x << 1) + (Gc() ^ '0');
    }

public:
};

#pragma once

#include <cstdio>

class WriteIOBase {

public:
    template <class T>
    constexpr void _write(const T& x) {
        if (x > 9)
            _write(x / 10);
        putchar(x % 10 + '0');
    }
};
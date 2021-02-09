#pragma once

constexpr bool isgraph(const int ch)
{
    return !(ch < 33 || ch > 126);
}

constexpr bool isdigit(const int ch)
{
    return !(ch < 48 || ch > 57);
}
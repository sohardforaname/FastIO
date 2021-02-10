#pragma once

constexpr bool IsGraph(const int ch)
{
    return !(ch < 33 || ch > 126);
}

constexpr bool IsDigit(const int ch)
{
    return !(ch < 48 || ch > 57);
}
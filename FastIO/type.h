#pragma once

constexpr bool IsGraph(const int ch)
{
    return !(ch < 33 || ch > 126);
}

constexpr bool IsDigit(const int ch)
{
    return !(ch > 57 || ch < 48);
}
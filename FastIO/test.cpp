#define _CRT_SECURE_NO_WARNINGS

#define useio

//#define usetestio

#ifdef useio
#include "IO.hpp"

#elif defined(usetestio)

#include "TestOtherIO.hpp"
#endif

#include <vector>
#include <ctime>
#include <chrono>
typedef long long ll;
using namespace std;
using namespace chrono;

bool multi = 0;
#ifdef useio
ReadIO io;

#endif // useio

const int N = 1e4 + 5;
vector<int> v;
vector<double> vd;
ll a[N], fileSize;
double db[N];
char s[N];
int suct, looptime;

void test1()
{
    int len = 1e7, a;
    looptime = len;

    for (int i = 0; i != len; ++i)
        suct += io(a);
}

void test2() {
    int len = 1e7;
    looptime = len;
    double a;

    for (int i = 1; i <= len; ++i)
        suct += io(a);
}

void test3() {
    int len = 1e4, sz = 1e4;
    looptime = len;

    for (int i = 1; i <= len; ++i) {
        suct += io(s);
    }
}

void test4() {
    int len = 1e4, sz = 1e3;
    looptime = len;

    for (int i = 1; i <= len; ++i)
        suct += io(ReadIO::make(v, sz));
}

void test5() {
    int len = 1e4, sz = 1e3;
    looptime = len;

    for (int i = 1; i <= len; ++i)
        suct += io(ReadIO::make(vd, sz));
}

void test() {
    int len = 1e7, a;
    looptime = len;
    fileSize = 98576811;

    for (int i = 0; i != len; ++i)
        suct += scanf("%d", &a);
}

void solve(int testcase) {
    auto st = steady_clock::now();
    switch (testcase) {
    case 1:
        test1();
        break;
    case 2:
        test2();
        break;
    case 3:
        test3();
        break;
    case 4:
        test4();
        break;
    case 5:
        test5();
        break;
    default:
        test();
    }
    auto ed = steady_clock::now();
    auto seg = duration_cast<milliseconds>(ed - st);

    auto time = seg.count();
    if (testcase < 6) {
        fileSize = io.GetReadSize();
    }
    printf("time: %lld ms\nfile size: %lld KByte(s)\n", time, fileSize >> 10);
    printf("speed: %.1f M/s\n", (fileSize >> 20) * 1000.0 / time);
    printf("run function times: %d\n", suct);
}

const char* path[]  = {
    "",
    "D:\\code\\vs\\C++_code\\FastIO\\data\\in1.txt",
    "D:\\code\\vs\\C++_code\\FastIO\\data\\in2.txt",
    "D:\\code\\vs\\C++_code\\FastIO\\data\\in3.txt",
    "D:\\code\\vs\\C++_code\\FastIO\\data\\in4.txt",
    "D:\\code\\vs\\C++_code\\FastIO\\data\\in5.txt"
};

int main(int argc, char** argv) {
    /*if (argc != 2)
        exit(0);
    int tsc = atoi(argv[1]);*/
    int tsc = 1;
    FILE* fp = NULL;
    if (tsc < 6)
        fp = freopen(path[tsc], "r", stdin);
    else
        fp = freopen("D:\\code\\vs\\C++_code\\FastIO\\data\\in1.txt", "r", stdin);
    
    int t;
    if (multi)
        io(t);
    else
        t = 1;
    while (t--)
        solve(tsc);
    return 0;
}

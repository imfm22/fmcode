// 231. Power of Two
// https://leetcode-cn.com/problems/power-of-two/

#include <stdio.h>
#include <assert.h>

// Solution
int isPowerOfTwo(int n);

int isPowerOfTwo(int n)
{
    if (n <= 0) {
        return 0;
    }

    return (n & (n - 1)) == 0;
}

/**************************************************/
/********************** test **********************/
/**************************************************/

int main()
{
    int test;
    test = isPowerOfTwo(-23456);
    assert(test == 0);

    test = isPowerOfTwo(0);
    assert(test == 0);

    test = isPowerOfTwo(1);
    assert(test == 1);

    test = isPowerOfTwo(8);
    assert(test == 1);

    test = isPowerOfTwo(1024);
    assert(test == 1);

    test = isPowerOfTwo(12345);
    assert(test == 0);

    return 0;
}

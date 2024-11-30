#include <stdio.h>
#include <inttypes.h>
#include "utl/utl.h"

#define run_test(test)                                                                                                 \
    do                                                                                                                 \
    {                                                                                                                  \
        printf("Running " #test "...\n");                                                                              \
        test();                                                                                                        \
        ++test_count;                                                                                                  \
    } while (0)

#define require(expr)                                                                                                  \
    do                                                                                                                 \
    {                                                                                                                  \
        assert_always((expr));                                                                                         \
        ++test_assert_count;                                                                                           \
    } while (0)

extern usize test_count;
extern usize test_assert_count;

#include "test.h"

usize test_count = 0;
usize test_assert_count = 0;

void test_arena(void);
void test_prng(void);
void test_str(void);
void test_utf(void);
void test_bytes(void);

int main(void)
{
    ThreadLocals locals;
    thread_locals_init_and_equip(&locals);
    printf("Beginning tests\n");
    test_arena();
    test_prng();
    test_str();
    test_utf();
    test_bytes();
    printf("Test complete (%" PRIu64 " assertions passed across %" PRIu64 " tests)\n", test_assert_count, test_count);
    thread_locals_release();
    return 0;
}

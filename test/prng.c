#include "test.h"

static void test_prng_seed(void)
{
    Prng prng = prng_seed(1477776061723855037U);
    require(prng.s[0] == 1985237415132408290U);
    require(prng.s[1] == 2979275885539914483U);
    require(prng.s[2] == 13511426838097143398U);
    require(prng.s[3] == 8488337342461049707U);
}

static void test_prng_next(void)
{
    Prng prng;
    for (usize i = 0; i < array_count(prng.s); i++)
    {
        prng.s[i] = i + 1;
    }
    u64 expected[] = {
        41943041U,
        58720359U,
        3588806011781223U,
        3591011842654386U,
        9228616714210784205U,
        9973669472204895162U,
        14011001112246962877U,
        12406186145184390807U,
        15849039046786891736U,
        10450023813501588000U,
    };
    for (usize i = 0; i < array_count(expected); i++)
    {
        u64 result = prng_next(&prng);
        require(result == expected[i]);
    }
}

static void test_prng_between(void)
{
    Prng prng = prng_seed(123);
    u64 min = 10;
    u64 max = 20;
    for (usize i = 0; i < 1000; i++)
    {
        u64 result = prng_between(&prng, min, max);
        require(result >= min);
        require(result < max);
    }
}

static void test_prng_next_f64(void)
{
    Prng prng = prng_seed(123);
    for (usize i = 0; i < 1000; i++)
    {
        f64 result = prng_next_f64(&prng);
        require(result >= 0.0);
        require(result < 1.0);
    }
}

static void test_prng_between_f64(void)
{
    Prng prng = prng_seed(123);
    f64 min = 10.0;
    f64 max = 20.0;
    for (usize i = 0; i < 1000; i++)
    {
        f64 result = prng_between_f64(&prng, min, max);
        require(result >= min);
        require(result < max);
    }
}

void test_prng(void)
{
    run_test(test_prng_seed);
    run_test(test_prng_next);
    run_test(test_prng_between);
    run_test(test_prng_next_f64);
    run_test(test_prng_between_f64);
}
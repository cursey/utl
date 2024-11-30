#include "test.h"

static void test_is_upper_is_lower(void)
{
    require(ascii_is_upper('A'));
    require(ascii_is_upper('Z'));
    require(!ascii_is_upper('a'));
    require(!ascii_is_upper('z'));
    require(!ascii_is_upper('1'));
    require(!ascii_is_upper('!'));
    require(ascii_is_lower('a'));
    require(ascii_is_lower('z'));
    require(!ascii_is_lower('A'));
    require(!ascii_is_lower('Z'));
    require(!ascii_is_lower('1'));
    require(!ascii_is_lower('!'));
}

static void test_to_upper_to_lower(void)
{
    require(ascii_to_upper('a') == 'A');
    require(ascii_to_upper('z') == 'Z');
    require(ascii_to_upper('A') == 'A');
    require(ascii_to_upper('Z') == 'Z');
    require(ascii_to_upper('1') == '1');
    require(ascii_to_upper('!') == '!');
    require(ascii_to_lower('A') == 'a');
    require(ascii_to_lower('Z') == 'z');
    require(ascii_to_lower('a') == 'a');
    require(ascii_to_lower('z') == 'z');
    require(ascii_to_lower('1') == '1');
    require(ascii_to_lower('!') == '!');
}

static void test_cstr_len(void)
{
    require(cstr_len((u8 *)"hello world") == 11);
    require(cstr16_len(u"hello world") == 11);
    require(cstr32_len(U"hello world") == 11);
}

static void test_str_starts_with(void)
{
    Str a = str_lit("hello world");
    require(str_starts_with(a, str_lit("hello")));
    require(str_starts_with(a, str_lit("hello world")));
    require(!str_starts_with(a, str_lit("world")));
    require(str_starts_with_i(a, str_lit("HELlo")));
    require(!str_starts_with_i(a, str_lit("HelLoo")));
}

static void test_str_ends_with(void)
{
    Str a = str_lit("hello world");
    require(str_ends_with(a, str_lit("world")));
    require(str_ends_with(a, str_lit("hello world")));
    require(!str_ends_with(a, str_lit("world!")));
    require(str_ends_with_i(a, str_lit("WOrlD")));
    require(!str_ends_with_i(a, str_lit("WOrlDd")));
}

static void test_str_cmp(void)
{
    require(str_cmp(str_lit("hello"), str_lit("hello")) == 0);
    require(str_cmp(str_lit("hello"), str_lit("world")) < 0);
    require(str_cmp(str_lit("world"), str_lit("hello")) > 0);
    require(str_cmp_i(str_lit("hello"), str_lit("HELLO")) == 0);
    require(str_cmp_i(str_lit("hello"), str_lit("WORLD")) < 0);
    require(str_cmp_i(str_lit("world"), str_lit("HELLO")) > 0);
}

static void test_str_eq(void)
{
    require(str_eq(str_lit("hello"), str_lit("hello")));
    require(!str_eq(str_lit("hello"), str_lit("world")));
    require(str_eq_i(str_lit("hello"), str_lit("HELLO")));
    require(!str_eq_i(str_lit("hello"), str_lit("WORLD")));
}

static void test_i64_from_str_base(void)
{
    // Positive.
    require(i64_from_str_base(str_lit("0"), 10) == 0);
    require(i64_from_str_base(str_lit("1"), 10) == 1);
    require(i64_from_str_base(str_lit("10"), 10) == 10);
    require(i64_from_str_base(str_lit("123"), 10) == 123);
    require(i64_from_str_base(str_lit("123"), 16) == 0x123);
    require(i64_from_str_base(str_lit("123"), 8) == 0123);

    // Negative.
    require(i64_from_str_base(str_lit("-1"), 10) == -1);
    require(i64_from_str_base(str_lit("-10"), 10) == -10);
    require(i64_from_str_base(str_lit("-123"), 10) == -123);
    require(i64_from_str_base(str_lit("-123"), 16) == -0x123);
    require(i64_from_str_base(str_lit("-123"), 8) == -0123);

    // Leading whitespace.
    require(i64_from_str_base(str_lit("  \t \n  \r 123"), 10) == 123);
    require(i64_from_str_base(str_lit("  \t \n  \r 123"), 16) == 0x123);
    require(i64_from_str_base(str_lit("  \t \n  \r 123"), 8) == 0123);
    require(i64_from_str_base(str_lit("  \t \n  \r -123"), 10) == -123);
    require(i64_from_str_base(str_lit("  \t \n  \r -123"), 16) == -0x123);
    require(i64_from_str_base(str_lit("  \t \n  \r -123"), 8) == -0123);
}

static void test_i64_from_str(void)
{
    // Positive.
    require(i64_from_str(str_lit("0")) == 0);
    require(i64_from_str(str_lit("1")) == 1);
    require(i64_from_str(str_lit("10")) == 10);
    require(i64_from_str(str_lit("123")) == 123);

    // Negative.
    require(i64_from_str(str_lit("-1")) == -1);
    require(i64_from_str(str_lit("-10")) == -10);
    require(i64_from_str(str_lit("-123")) == -123);

    // Leading whitespace.
    require(i64_from_str(str_lit("  \t \n  \r 123")) == 123);
    require(i64_from_str(str_lit("  \t \n  \r -123")) == -123);
}

static void test_f64_from_str(void)
{
    // Positive.
    require(f64_from_str(str_lit("0")) == 0.0);
    require(f64_from_str(str_lit("1")) == 1.0);
    require(f64_from_str(str_lit("10")) == 10.0);
    require(f64_from_str(str_lit("123")) == 123.0);
    require(f64_from_str(str_lit("123.456")) == 123.456);
    require(f64_from_str(str_lit("123.456e3")) == 123.456e3);
    require(f64_from_str(str_lit("123.456e-3")) == 123.456e-3);

    // Negative.
    require(f64_from_str(str_lit("-1")) == -1.0);
    require(f64_from_str(str_lit("-10")) == -10.0);
    require(f64_from_str(str_lit("-123")) == -123.0);
    require(f64_from_str(str_lit("-123.456")) == -123.456);
    require(f64_from_str(str_lit("-123.456e3")) == -123.456e3);
    require(f64_from_str(str_lit("-123.456e-3")) == -123.456e-3);

    // Leading whitespace.
    require(f64_from_str(str_lit("  \t \n  \r 123")) == 123.0);
    require(f64_from_str(str_lit("  \t \n  \r -123")) == -123.0);
    require(f64_from_str(str_lit("  \t \n  \r 123.456")) == 123.456);
    require(f64_from_str(str_lit("  \t \n  \r -123.456")) == -123.456);
}

static void test_str_escape(void)
{
    Temp scratch = scratch_begin(0, 0);
    Str a = str_lit("hello\nworld");
    Str b = str_escape(scratch.arena, a);
    require(str_eq(b, str_lit("hello\\nworld")));
    scratch_end(scratch);
}

static void test_str_unescape(void)
{
    Temp scratch = scratch_begin(0, 0);
    Str a = str_lit("hello\\nworld");
    Str b = str_unescape(scratch.arena, a);
    require(str_eq(b, str_lit("hello\nworld")));
    scratch_end(scratch);
}

static void test_str_find(void)
{
    Str a = str_lit("hello world");
    require(str_find(a, str_lit("hello")) == 0);
    require(str_find(a, str_lit("world")) == 6);
    require(str_find(a, str_lit(" ")) == 5);
    require(str_find(a, str_lit("x")) == a.len);
    require(str_find(a, str_lit("world!")) == a.len);
}

static void test_str_find_i(void)
{
    Str a = str_lit("hello world");
    require(str_find_i(a, str_lit("HELLO")) == 0);
    require(str_find_i(a, str_lit("WORLD")) == 6);
    require(str_find_i(a, str_lit(" ")) == 5);
    require(str_find_i(a, str_lit("X")) == a.len);
    require(str_find_i(a, str_lit("WORLD!")) == a.len);
}

static void test_str_rfind(void)
{
    Str a = str_lit("hello world");
    require(str_rfind(a, str_lit("hello")) == 0);
    require(str_rfind(a, str_lit("world")) == 6);
    require(str_rfind(a, str_lit(" ")) == 5);
    require(str_rfind(a, str_lit("x")) == a.len);
    require(str_rfind(a, str_lit("world!")) == a.len);
    require(str_rfind(a, str_lit("l")) == 9);
}

static void test_str_rfind_i(void)
{
    Str a = str_lit("hello world");
    require(str_rfind_i(a, str_lit("HELLO")) == 0);
    require(str_rfind_i(a, str_lit("WORLD")) == 6);
    require(str_rfind_i(a, str_lit(" ")) == 5);
    require(str_rfind_i(a, str_lit("X")) == a.len);
    require(str_rfind_i(a, str_lit("WORLD!")) == a.len);
    require(str_rfind_i(a, str_lit("L")) == 9);
}

static void test_str_substr(void)
{
    Str a = str_lit("hello world");
    Str b = str_substr(a, 0, 5);
    require(str_eq(b, str_lit("hello")));
    b = str_substr(a, 6, 5);
    require(str_eq(b, str_lit("world")));
    b = str_substr(a, 0, -1);
    require(str_eq(b, a));
}

void test_str(void)
{
    run_test(test_is_upper_is_lower);
    run_test(test_to_upper_to_lower);
    run_test(test_cstr_len);
    run_test(test_str_starts_with);
    run_test(test_str_ends_with);
    run_test(test_str_cmp);
    run_test(test_str_eq);
    run_test(test_i64_from_str_base);
    run_test(test_i64_from_str);
    run_test(test_f64_from_str);
    run_test(test_str_escape);
    run_test(test_str_unescape);
    run_test(test_str_find);
    run_test(test_str_find_i);
    run_test(test_str_rfind);
    run_test(test_str_rfind_i);
    run_test(test_str_substr);
}
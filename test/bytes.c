#include "test.h"

static void test_make_bytes_pattern(void)
{
    Temp scratch = scratch_begin(0, 0);
    Str pattern = str_lit("AB CD ? EF ? ? 12 34");
    BytesPattern *bytes_pattern = make_bytes_pattern(scratch.arena, pattern);
    require(bytes_pattern->len == 8);
    require(bytes_pattern->bytes[0] == 0xAB);
    require(bytes_pattern->bytes[1] == 0xCD);
    require(bytes_pattern->bytes[2] == -1);
    require(bytes_pattern->bytes[3] == 0xEF);
    require(bytes_pattern->bytes[4] == -1);
    require(bytes_pattern->bytes[5] == -1);
    require(bytes_pattern->bytes[6] == 0x12);
    require(bytes_pattern->bytes[7] == 0x34);
    scratch_end(scratch);
}

static void test_bytes_scan(void)
{
    u8 *mem = (u8 *)"Hello, world! Goodbye, world! Hello again, world!";
    Bytes bytes = {.ptr = mem, .len = cstr_len(mem)};
    require(bytes_scan(bytes, str_lit("77 6F 72 6C 64")) == mem + 7);    // "world"
    require(bytes_scan(bytes, str_lit("61 67 61 69 6E")) == mem + 36);   // "again"
    require(bytes_scan(bytes, str_lit("47 ? ? 64 ? ? 65")) == mem + 14); // "Goodbye"
}

static void test_bytes_from_str(void)
{
    Bytes bytes = bytes_from_str(str_lit("Hello, world!"));
    require(bytes_scan(bytes, str_lit("77 6F 72 6C 64")) == bytes.ptr + 7);
}

static void test_bytes_pattern_from_str(void)
{
    Temp scratch = scratch_begin(0, 0);
    u8 *mem = (u8 *)"Hello, world! Goodbye, world! Hello again, world!";
    Bytes bytes = {.ptr = mem, .len = cstr_len(mem)};
    require(bytes_scan_pattern(bytes, bytes_pattern_from_str(scratch.arena, str_lit("world"))) == mem + 7);
    require(bytes_scan_pattern(bytes, bytes_pattern_from_str(scratch.arena, str_lit("again"))) == mem + 36);
    require(bytes_scan_pattern(bytes, bytes_pattern_from_str(scratch.arena, str_lit("Goodbye"))) == mem + 14);
    scratch_end(scratch);
}

void test_bytes(void)
{
    run_test(test_make_bytes_pattern);
    run_test(test_bytes_scan);
    run_test(test_bytes_from_str);
    run_test(test_bytes_pattern_from_str);
}
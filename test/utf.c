#include "test.h"
#include "utl/utl.h"

static void test_utf8_decode(void)
{
    UnicodeDecode a = utf8_decode((u8 *)"hello", 5);
    require(a.inc == 1);
    require(a.codepoint == 'h');
    UnicodeDecode b = utf8_decode((u8 *)"world", 5);
    require(b.inc == 1);
    require(b.codepoint == 'w');
    UnicodeDecode c = utf8_decode((u8 *)"\xf0\x9f\x98\x80", 4);
    require(c.inc == 4);
    require(c.codepoint == 0x1f600);
}

static void test_utf16_decode(void)
{
    UnicodeDecode a = utf16_decode((u16 *)u"hello", 5);
    require(a.inc == 1);
    require(a.codepoint == 'h');
    UnicodeDecode b = utf16_decode((u16 *)u"world", 5);
    require(b.inc == 1);
    require(b.codepoint == 'w');
    UnicodeDecode c = utf16_decode((u16 *)u"\xd801\xdc37", 2);
    require(c.inc == 2);
    require(c.codepoint == 0x10437);
}

void test_utf(void)
{
    run_test(test_utf8_decode);
    run_test(test_utf16_decode);
}
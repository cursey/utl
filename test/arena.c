#include "test.h"

static void test_arena_allocation_and_release(void)
{
    Arena *arena = arena_alloc();
    require(arena != 0);
    arena_release(arena);
}

static void test_arena_push_and_pop(void)
{
    Arena *arena = arena_alloc();
    require(arena != 0);
    usize start_pos = arena_pos(arena);
    require(arena_push(arena, 4, 4) != 0);
    require(arena_push(arena, 4, 4) != 0);
    require(arena_push(arena, 4, 4) != 0);
    require(arena_pos(arena) == start_pos + 4 * 3);
    arena_pop(arena, 4);
    require(arena_pos(arena) == start_pos + 4 * 2);
    arena_pop(arena, 4);
    require(arena_pos(arena) == start_pos + 4 * 1);
    arena_pop(arena, 4);
    require(arena_pos(arena) == start_pos);
    arena_pop(arena, 4);
    require(arena_pos(arena) == start_pos);
    arena_release(arena);
}

static void test_arena_clear(void)
{
    Arena *arena = arena_alloc();
    require(arena != 0);
    usize start_pos = arena_pos(arena);
    require(arena_push(arena, 4, 4) != 0);
    require(arena_push(arena, 4, 4) != 0);
    require(arena_push(arena, 4, 4) != 0);
    require(arena_pos(arena) == start_pos + 12);
    arena_clear(arena);
    require(arena_pos(arena) == start_pos);
    arena_release(arena);
}

static void test_arena_macro_push_array_no_zero_aligned(Arena *arena)
{
    int *arr = push_array_no_zero_aligned(arena, int, 4, 8);
    require(arr != 0);
    require((uintptr_t)arr % 8 == 0);
    require(arr[0] != 0);
    require(arr[1] != 0);
    require(arr[2] != 0);
    require(arr[3] != 0);
}

static void test_arena_macro_push_array_aligned(Arena *arena)
{
    int *arr = push_array_aligned(arena, int, 4, 8);
    require(arr != 0);
    require((uintptr_t)arr % 8 == 0);
    require(arr[0] == 0);
    require(arr[1] == 0);
    require(arr[2] == 0);
    require(arr[3] == 0);
}

static void test_arena_macro_push_array_no_zero(Arena *arena)
{
    int *arr = push_array_no_zero(arena, int, 4);
    require(arr != 0);
    require((uintptr_t)arr % sizeof(int) == 0);
    require(arr[0] != 0);
    require(arr[1] != 0);
    require(arr[2] != 0);
    require(arr[3] != 0);
}

static void test_arena_macro_push_array(Arena *arena)
{
    int *arr = push_array(arena, int, 4);
    require(arr != 0);
    require((uintptr_t)arr % sizeof(int) == 0);
    require(arr[0] == 0);
    require(arr[1] == 0);
    require(arr[2] == 0);
    require(arr[3] == 0);
}

static void test_arena_macros(void)
{
    typedef void (*MacroTestFn)(Arena *);
    MacroTestFn macro_tests[] = {
        test_arena_macro_push_array_no_zero_aligned,
        test_arena_macro_push_array_aligned,
        test_arena_macro_push_array_no_zero,
        test_arena_macro_push_array,
    };
    for (usize i = 0; i < array_count(macro_tests); i++)
    {
        Arena *arena = arena_alloc();
        require(arena != 0);

        // Fill with garbage.
        char *p = arena_push(arena, 32, 1);
        mem_set(p, 0x42, 32);
        arena_pop(arena, 32);

        // Force bad alignment.
        arena_push(arena, 1, 1);
        require(arena_pos(arena) % 8 != 0);

        // Run the test.
        macro_tests[i](arena);
        arena_release(arena);
    }
}

static void test_arena_grow(void)
{
    Arena *arena = arena_alloc(.commit = 0x1000);
    require(arena != 0);

    // Allocate a buffer bigger than the currently committed size.
    void *a1 = arena_push(arena, 0x10000, 1);
    require(a1 != 0);

    // Probe each page.
    for (int i = 0; i < 0x10000; i += 0x1000)
    {
        require(*((u8 *)a1 + i) == 0);
    }
    arena_release(arena);
}

static void test_scratch_arena(void)
{
    Temp scratch = scratch_begin(0, 0);
    require(scratch.arena != 0);
    void *a1 = arena_push(scratch.arena, 1024, 1);
    require(a1 != 0);
    void *a2 = arena_push(scratch.arena, 1024, 1);
    require(a2 != 0);
    void *a3 = arena_push(scratch.arena, 1024, 1);
    require(a3 != 0);
    require(a1 != a2);
    require(a2 != a3);
    require(a3 != a1);
    temp_end(scratch);
}

static void test_scratch_arena_with_conflicts(void)
{
    Temp scratch1 = scratch_begin(0, 0);
    require(scratch1.arena != 0);
    Temp scratch2 = scratch_begin(&scratch1.arena, 1);
    require(scratch2.arena != 0);
    require(scratch1.arena != scratch2.arena);
    temp_end(scratch2);
    temp_end(scratch1);
}

void test_arena(void)
{
    run_test(test_arena_allocation_and_release);
    run_test(test_arena_push_and_pop);
    run_test(test_arena_clear);
    run_test(test_arena_macros);
    run_test(test_arena_grow);
    run_test(test_scratch_arena);
    run_test(test_scratch_arena_with_conflicts);
}
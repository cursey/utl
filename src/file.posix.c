#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include "utl/thread.h"
#include "utl/utf.h"
#include "utl/file.h"

StrList file_walk(Arena *arena, Str directory)
{
    typedef struct Task Task;
    struct Task
    {
        Task *next;
        Str dir;
    };
    Task start_task = {.next = 0, .dir = directory};
    Task *head_task = &start_task;
    Task *tail_task = &start_task;
    StrList result = {0};
    Temp scratch = scratch_begin(&arena, 1);
    for (Task *task = head_task; task != 0; task = task->next)
    {
        Str pat = push_str_cat(scratch.arena, task->dir, str_lit("/*"));
        DIR *dir = opendir(task->dir.ptr);
        if (dir == 0)
        {
            continue;
        }
        struct dirent *entry;
        while ((entry = readdir(dir)) != 0)
        {
            Str name = str_from_cstr(scratch.arena, entry->d_name);
            Str path = push_strf(scratch.arena, "%.*s/%.*s", str_varg(task->dir), str_varg(name));
            struct stat path_stat;
            stat(path.ptr, &path_stat);
            if (S_ISDIR(path_stat.st_mode))
            {
                if (entry->d_name[0] != '.')
                {
                    Task *next_task = push_array(scratch.arena, Task, 1);
                    next_task->dir = path;
                    queue_push(head_task, tail_task, next_task);
                }
            }
            else
            {
                str_list_push(arena, &result, push_str_copy(arena, path));
            }
        }
        closedir(dir);
    }
    scratch_end(scratch);
    return result;
}

Str file_cwd(Arena *arena)
{
    Temp scratch = scratch_begin(&arena, 1);
    long size = pathconf(".", _PC_PATH_MAX);
    u8 *buf = push_array(scratch.arena, u8, size);
    Str result = str_from_cstr(arena, getcwd((char *)buf, size));
    temp_end(scratch);
    return result;
}
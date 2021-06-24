/*
 * Copyright (c) 2021 nuke123-sudo
 *
 * SPDX-License-Identifier: BSD-2-Clause
*/

// includes
#include <arpa/inet.h>
#include <errno.h>
#include <serenity.h>
#include <string.h>
#include <syscall.h>


extern "C" {

int disown(pid_t pid)
{
    int rc = syscall(SC_disown, pid);
    __RETURN_WITH_ERRNO(rc, rc, -1);
}

int module_load(const char* path, size_t path_length)
{
    int rc = syscall(SC_module_load, path, path_length);
    __RETURN_WITH_ERRNO(rc, rc, -1);
}

int module_unload(const char* name, size_t name_length)
{
    int rc = syscall(SC_module_unload, name, name_length);
    __RETURN_WITH_ERRNO(rc, rc, -1);
}

int profiling_enable(pid_t pid, uint64_t event_mask)
{
    int rc = syscall(SC_profiling_enable, pid, event_mask);
    __RETURN_WITH_ERRNO(rc, rc, -1);
}


}
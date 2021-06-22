/*
 * Copyright (c) 2021, Krisna Pranav
 *
 * SPDX-License-Identifier: BSD-2-Clause
*/

// includes
#include <AK/Assertions.h>
#include <libgen.h>
#include <string.h>

static char dot[] = ".";
static char slash[] = "/";

char* dirname(char* path)
{
    if (path == nullptr)
        return dot;

    int len = strlen(path);
    if (len == 0)
        return dot;

    while (len > 1 && path[len - 1] == '/') {
        path[len - 1] = 0;
        len--;
    }

    char* last_slash = strrchr(path, '/');
    if (last_slash == nullptr)
        return dot;

    if (last_slash == path)
        return slash;

    *last_slash = 0;
    return path;
}
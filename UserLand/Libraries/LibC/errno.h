/*
 * Copyright (c) 2021, Krisna Pranav
 *
 * SPDX-License-Identifier: BSD-2-Clause
*/

#pragma once

// includes
#include <errno_numbers.h>
#include <sys/cdefs.h>

#define __RETURN_WITH_ERRNO(rc, good_ret, bad_ret) \
    do {                                           \
        if (rc < 0) {                              \
            errno = -rc;                           \
            return (bad_ret);                      \
        }                                          \
        return (good_ret);                         \
    } while (0)

__BEGIN_DECLS
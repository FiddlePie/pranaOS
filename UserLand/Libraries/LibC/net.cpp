/*
 * Copyright (c) 2021, Krisna Pranav
 *
 * SPDX-License-Identifier: BSD-2-Clause
*/

// includes
#include <LibC/errno.h>
#include <LibC/net/if.h>
#include <LibC/netinet/in.h>

in6_addr in6addr_any = IN6ADDR_ANY_INIT;


unsigned int if_nametoindex([[maybe_unused]] const char* ifname)
{
    errno = ENODEV;
    return -1;
}
/*
 * Copyright (c) 2021, Krisna Pranav
 *
 * SPDX-License-Identifier: BSD-2-Clause
*/

// includes
#include <errno.h>
#include <poll.h>
#include <sys/time.h>
#include <syscall.h>

extern "C" {

  int poll(pollfd* fds, nfds_t nfds, int timeout_ms)
  {
      timespec timeout;
      timespec* timeout_ts = &timeout;
      if (timeout_ms < 0)
          timeout_ts = nullptr;
      else
          timeout = { timeout_ms / 1000, (timeout_ms % 1000) * 1'000'000 };
      return ppoll(fds, nfds, timeout_ts, nullptr);
  }

}

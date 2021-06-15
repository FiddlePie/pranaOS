/*
 * Copyright (c) 2021, Krisna Pranav
 *
 * SPDX-License-Identifier: BSD-2-Clause
*/

// includes
#include <LibAudio/Buffer.h>
#include <LibAudio/ClientConnection.h>

namespace Audio {

ClientConnection::ClientConnection()
    : IPC::ServerConnection<AudioClientEndpoint, AudioServerEndpoint>(*this, "/tmp/portal/audio")
{
}

void ClientConnection::enqueue(const Buffer& buffer)
{
    for (;;) {
        auto success = enqueue_buffer(buffer.anonymous_buffer(), buffer.id(), buffer.sample_count());
        if (success)
            break;
        sleep(1);
    }
}

bool ClientConnection::try_enqueue(const Buffer& buffer)
{
    return enqueue_buffer(buffer.anonymous_buffer(), buffer.id(), buffer.sample_count());
}

void ClientConnection::finished_playing_buffer(i32 buffer_id)
{
    if (on_finish_playing_buffer)
        on_finish_playing_buffer(buffer_id);
}


}
/*
 * (C) Copyright 1996-2017 ECMWF.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 * In applying this licence, ECMWF does not waive the privileges and immunities
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/socket.h>

#include "eckit/log/Log.h"
#include "eckit/io/Select.h"
#include "eckit/web/ProxiedTCPServer.h"

//-----------------------------------------------------------------------------

namespace eckit {

//-----------------------------------------------------------------------------

ProxiedTCPServer::ProxiedTCPServer(int port, const std::string& addr):
    TCPServer(port, addr)
{
}

ProxiedTCPServer::~ProxiedTCPServer()
{
}

// Accept a client

TCPSocket& ProxiedTCPServer::accept(const std::string& message, int timeout, bool* connected)
{
    TCPSocket& socket = TCPServer::accept(message, timeout, connected);

    // Strip http-header

    char c;
    unsigned long x = 0;
    unsigned long end = ('\r' << 24L) | ('\n' << 16L ) | ('\r' << 8L) | '\n';

    while (socket.read(&c, 1) == 1) {

        x <<= 8L;
        x |= c;
        x &= 0xffffffff;

        if (x == end)
            return socket;
    }

    throw SeriousBug("ProxiedTCPServer: invalid header");
}

//-----------------------------------------------------------------------------

} // namespace eckit


/*
 * (C) Copyright 1996- ECMWF.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 * In applying this licence, ECMWF does not waive the privileges and immunities
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

#include "eckit/web/HtmlResource.h"
#include "eckit/web/HttpBuf.h"
#include "eckit/web/HttpService.h"
#include "eckit/web/HttpUser.h"
#include "eckit/web/Url.h"
#include "eckit/io/TCPSocketHandle.h"
#include "eckit/config/Resource.h"
#include "eckit/runtime/Monitor.h"

//-----------------------------------------------------------------------------

namespace eckit {

//-----------------------------------------------------------------------------

HttpService::HttpService(int port, bool visible):
	NetService(port, visible)
{
}

HttpService::~HttpService()
{
}


NetUser* HttpService::newUser(TCPSocket& protocol)
{
	return new HttpUser(protocol);
}

//-----------------------------------------------------------------------------

HttpUser::HttpUser(TCPSocket& protocol):
	NetUser(protocol)
{
}

HttpUser::~HttpUser()
{
}

void HttpUser::serve(eckit::Stream& s, std::istream& in, std::ostream& out)
{
	static bool debug = Resource<bool>("-debug-http", false);
	protocol_.debug(debug);

	HttpStream http;

	Url url(in);
	Monitor::instance().name(url.method());

	try {
		HtmlResource::dispatch(s, in, http, url);
	}
	catch (std::exception& e)
	{
		Log::error() << "** " << e.what() << " Caught in "
		             << Here() << std::endl;
		Log::error() << "** Exception is ignored" << std::endl;
		http << "Exception caught: " << e.what() << std::endl;
		return;
	}



	InstantTCPSocketHandle stream(protocol_);
	http.write(out, url, stream);

	Monitor::instance().show(false);

}

//-----------------------------------------------------------------------------

} // namespace eckit


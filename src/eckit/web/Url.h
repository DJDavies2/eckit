/*
 * (C) Copyright 1996- ECMWF.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 * In applying this licence, ECMWF does not waive the privileges and immunities
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

// File Url.h
// Baudouin Raoult - ECMWF Oct 96

#ifndef Url_H
#define Url_H

#include "eckit/value/Value.h"
#include "eckit/web/HttpHeader.h"
#include "eckit/memory/ScopedPtr.h"

//-----------------------------------------------------------------------------

namespace eckit {

//-----------------------------------------------------------------------------

class Url;

//-----------------------------------------------------------------------------

class UrlAccess {
	Url&   url_;
	std::string s_;


public:
	UrlAccess(Url& url, const std::string& s) : url_(url), s_(s) {}

	operator std::string();
	operator long();

	UrlAccess& operator=(const std::string&);
	UrlAccess& operator=(long);
};

//-----------------------------------------------------------------------------

class Url : private eckit::NonCopyable {
public:

	enum {
		notFound = 404
	};

// -- Contructors

	Url(std::istream&);
	Url(const std::string&);

// -- Destructor

	~Url();

// -- Operators

	UrlAccess operator[](const std::string&);

// -- Methods

	void erase(const std::string&);


	void set(const std::string&, const std::string&);
	const std::string& get(const std::string&);

	const std::string& method() { return method_;}


	HttpHeader&   headerIn();
	HttpHeader&   headerOut();

	const HttpHeader&   headerIn() const;
	const HttpHeader&   headerOut() const;

	std::string str() const;
	std::string name() const;


	int size() const;
	const std::string& operator[](int) const;

	bool authenticated() {
		return headerIn().authenticated();
	}

	void authenticate(const std::string& realm = "MARS") {
		headerOut().authenticate(realm);
	}

	void status(int s, const std::string& message = "") {
		headerOut().status(s, message);
	}

	void type(const std::string& type) {
		headerOut().type(type);
	}

	void forward(const std::string& s) {
		headerOut().forward(s);
	}

	void location(const std::string& s) {
		headerOut().forward(s);
	}

	void retryAfter(long s) {
		headerOut().retryAfter(s);
	}

	void dontCache() {
		headerOut().dontCache();
	}

	void cgiParam(std::ostream&, char sep = ' ') const;

	eckit::Value json() const;

	void remaining(const std::vector<std::string>& remaining) {
		remaining_ = remaining;
	}

	const std::vector<std::string>& remaining() const {
		return remaining_;
	}

	void streamFrom(DataHandle*);

	DataHandle* streamFrom();

protected:

// -- Methods

	void print(std::ostream&) const;

private:

// -- Members

	typedef std::map<std::string, std::string, std::less<std::string> > Map;

	Map            map_;
	std::vector<std::string> url_;
	HttpHeader     in_;
	HttpHeader     out_;

	std::string		   method_;

	std::vector<std::string> remaining_;

	eckit::ScopedPtr<DataHandle> handle_;


// -- Methods

	void parse(const std::string&, bool);
	void parse(std::istream&);

// -- Friends

	friend std::ostream& operator<<(std::ostream& s, const Url& p)
	{ p.print(s); return s; }

};

//-----------------------------------------------------------------------------

} // namespace eckit


#endif

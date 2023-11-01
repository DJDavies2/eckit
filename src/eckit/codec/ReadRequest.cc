/*
 * (C) Copyright 1996- ECMWF.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 *
 * In applying this licence, ECMWF does not waive the privileges and immunities
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */


#include "eckit/codec/ReadRequest.h"

#include "eckit/codec/RecordItemReader.h"
#include "eckit/codec/detail/Checksum.h"
#include "eckit/codec/detail/Defaults.h"
#include "eckit/exception/Exceptions.h"
#include "eckit/log/Log.h"

namespace eckit::codec {

static std::string stream_path(Stream stream) {
    std::stringstream s;
    s << &stream.datahandle();
    return s.str();
}

//---------------------------------------------------------------------------------------------------------------------

ReadRequest::ReadRequest(const std::string& URI, Decoder* decoder) :
    uri_(URI), decoder_(decoder), item_(new RecordItem()) {
    do_checksum_ = defaults::checksum_read();
    ASSERT(!uri_.empty());
}

ReadRequest::ReadRequest(Stream stream, size_t offset, const std::string& key, Decoder* decoder) :
    stream_{stream},
    offset_{offset},
    key_{key},
    uri_{"stream:" + stream_path(stream) + "?offset=key=" + key_},
    decoder_(decoder),
    item_(new RecordItem()) {
    do_checksum_ = defaults::checksum_read();
    ASSERT(stream_);
}

//---------------------------------------------------------------------------------------------------------------------

ReadRequest::ReadRequest(ReadRequest&& other) :
    stream_{other.stream_},
    offset_{other.offset_},
    key_{other.key_},
    uri_(std::move(other.uri_)),
    decoder_(std::move(other.decoder_)),
    item_(std::move(other.item_)),
    do_checksum_{other.do_checksum_},
    finished_{other.finished_} {
    other.do_checksum_ = true;
    other.finished_    = true;
}

//---------------------------------------------------------------------------------------------------------------------

ReadRequest::~ReadRequest() {
    if (item_) {
        if (not finished_) {
            Log::error() << "Request for " << uri_ << " was not completed." << std::endl;
        }
    }
}

//---------------------------------------------------------------------------------------------------------------------

void ReadRequest::read() {
    if (item_->empty()) {
        if (stream_) {
            RecordItemReader{stream_, offset_, key_}.read(*item_);
        }
        else {
            RecordItemReader(uri_).read(*item_);
        }
    }
}

//---------------------------------------------------------------------------------------------------------------------

void ReadRequest::checksum(bool b) {
    do_checksum_ = b;
}

void ReadRequest::checksum() {
    if (not do_checksum_) {
        return;
    }

    Checksum encoded_checksum{item_->metadata().data.checksum()};

    if (not encoded_checksum.available()) {
        return;
    }

    Checksum computed_checksum{item_->data().checksum(encoded_checksum.algorithm())};

    if (computed_checksum.available() && (computed_checksum.str() != encoded_checksum.str())) {
        std::stringstream err;
        err << "Mismatch in checksums for " << uri_ << ".\n";
        err << "        Encoded:  [" << encoded_checksum.str() << "].\n";
        err << "        Computed: [" << computed_checksum.str() << "].";
        throw DataCorruption(err.str());
    }
    do_checksum_ = false;
}

//---------------------------------------------------------------------------------------------------------------------

void ReadRequest::decompress() {
    read();
    item_->decompress();
}

//---------------------------------------------------------------------------------------------------------------------

void ReadRequest::decode() {
    decompress();
    codec::decode(item_->metadata(), item_->data(), *decoder_);
    item_->clear();
}

//---------------------------------------------------------------------------------------------------------------------

void ReadRequest::wait() {
    if (item_) {
        if (not finished_) {
            read();
            checksum();
            decompress();
            decode();
        }
        finished_ = true;
    }
}

//---------------------------------------------------------------------------------------------------------------------

}  // namespace eckit::codec

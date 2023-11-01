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


#include "eckit/codec/print/JSONFormat.h"

#include "eckit/codec/Record.h"
#include "eckit/codec/RecordItemReader.h"
#include "eckit/codec/Session.h"
#include "eckit/log/JSON.h"

namespace eckit::codec {

JSONFormat::JSONFormat(const Record::URI& record, const Configuration& config) :
    record_(Session::record(record.path, record.offset)) {
    for (const auto& key : record_.keys()) {
        items_.emplace(key, Metadata());
        RecordItemReader{RecordItem::URI{record.path, record.offset, key}}.read(items_.at(key));
    }

    config.get("details", print_details_);
}

void JSONFormat::print(std::ostream& out) const {
    JSON js(out, JSON::Formatting::indent(4));

    Metadata metadata;
    for (const auto& key : record_.keys()) {
        const auto& item = items_.at(key);

        Metadata m = record_.metadata(key);

        if (record_.metadata(key).link()) {
            m.set(item);
            if (m.has("data")) {  // removes data.section
                m.remove("data");
            }
        }

        if (not print_details_) {
            if (m.has("data")) {
                m.remove("data");
            }
        }

        if (print_details_) {
            if (item.data.size() > 0) {
                m.set("data.compression.type", item.data.compression());
                m.set("data.compression.size", item.data.compressed_size());
                m.set("data.size", item.data.size());
                m.set("data.byte_order", (item.data.endian() == Endian::little) ? "little endian" : "big endian");
                m.set("data.checksum", item.data.checksum().str());
            }
            m.set("version", item.record.version().str());
            m.set("created", item.record.created().str());
        }


        metadata.set(key, m);
    }
    js << metadata;
}


}  // namespace eckit::codec

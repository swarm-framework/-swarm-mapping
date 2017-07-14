/*
 * Copyright 2017 Damien Giron <contact@damiengiron.me>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include "RapidJSONEncoder.hxx"

#include <swarm/exception/SwarmException.hxx>

#include <rapidjson/writer.h>

namespace swarm {
    namespace mapping {

        RapidJSONEncoder::RapidJSONEncoder()
            : stringBuffer(std::make_shared<StringBuffer>()),
              writer(std::make_shared<Writer<StringBuffer>>(*stringBuffer)) {
            writer->StartObject();
        }

        RapidJSONEncoder::RapidJSONEncoder(std::shared_ptr<StringBuffer> stringBuffer,
                                           std::shared_ptr<Writer<StringBuffer>> writer)
            : stringBuffer(stringBuffer), writer(writer) {
            writer->StartObject();
        }

        RapidJSONEncoder::~RapidJSONEncoder() {
            if (open) {
                writer->EndObject();
            }
        }

        void RapidJSONEncoder::encodeInt(const std::string &name, int value) {
            writer->Key(name.c_str());
            writer->Int(value);
        }

        void RapidJSONEncoder::encodeString(const std::string &name, const std::string &value) {
            writer->Key(name.c_str());
            writer->String(value.c_str());
        }

        std::shared_ptr<ObjectEncoder> RapidJSONEncoder::subObjectEncoder(const std::string &name) {
            writer->Key(name.c_str());
            return std::shared_ptr<ObjectEncoder>{new RapidJSONEncoder{stringBuffer, writer}};
        }

        void RapidJSONEncoder::write(std::ostream &ostream) {
            if (open) {
                writer->EndObject();
                open = false;
            }
            ostream << stringBuffer->GetString();
        }
    }
}

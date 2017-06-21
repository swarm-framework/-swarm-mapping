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

#ifndef SWARM_MAPPING_RAPIDJSONENCODER_HXX
#define SWARM_MAPPING_RAPIDJSONENCODER_HXX

#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include <ostream>
#include <memory>

using namespace rapidjson;

namespace swarm {
    namespace mapping {

        /// \brief Class RapidJSONEncoder
        class RapidJSONEncoder {
            
        private:
            
            std::shared_ptr<StringBuffer> stringBuffer;
            
            std::shared_ptr<Writer<StringBuffer>> writer;
            
            bool open = true;
            
        public:
            
            RapidJSONEncoder();
            RapidJSONEncoder(std::shared_ptr<StringBuffer> stringBuffer, std::shared_ptr<Writer<StringBuffer>> writer);
            ~RapidJSONEncoder();
            
            template <typename T>
            void encode(const std::string & name, const T & value);
            
            void write(std::ostream & ostream);
            
            std::shared_ptr<RapidJSONEncoder> subObject(const std::string & name);
        };
    }
}

#include "RapidJSONEncoder.txx"

#endif // SWARM_MAPPING_RAPIDJSONENCODER_HXX

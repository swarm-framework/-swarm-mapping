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
#include <string>

#include "../ObjectProvider.hxx"

using namespace rapidjson;

namespace swarm {
    namespace mapping {
                
        /// \brief Class RapidJSONEncoder
        class RapidJSONEncoder : public ObjectEncoder {
            
        private:
            
            /// \brief String buffer
            std::shared_ptr<StringBuffer> stringBuffer;
            
            /// \brief Writer
            std::shared_ptr<Writer<StringBuffer>> writer;
            
            /// \brief JSon opened
            bool open = true;
            
            
            /// \brief Sub element constructor
            /// \param stringBuffer RapidJson string buffer
            /// \param writer RapidJson writer
            RapidJSONEncoder(std::shared_ptr<StringBuffer> stringBuffer, std::shared_ptr<Writer<StringBuffer>> writer);
            
        public:
            
            /// \brief Defauft constructor
            RapidJSONEncoder();
            
            /// \brief Destructor
            /// Used to close buffer if opened
            ~RapidJSONEncoder();
            
            // Override encode int
            virtual void encodeInt(const std::string & name, int value) override;
            
            // Override encode string
            virtual void encodeString(const std::string & name, const std::string & value) override;
            
            // Override create new sub object encoder
            virtual std::shared_ptr<ObjectEncoder> subObjectEncoder(const std::string & name) override;
            
            /// \brief Write docmu
            void write(std::ostream & ostream);
        };
    }
}

#endif // SWARM_MAPPING_RAPIDJSONENCODER_HXX

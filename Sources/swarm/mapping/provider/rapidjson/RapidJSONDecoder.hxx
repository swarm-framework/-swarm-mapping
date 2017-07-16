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

#ifndef SWARM_MAPPING_RAPIDJSONDECODER_HXX
#define SWARM_MAPPING_RAPIDJSONDECODER_HXX

#include <optional>
#include <rapidjson/document.h>
#include <istream>

#include "../ObjectProvider.hxx"

using namespace rapidjson;

namespace swarm {
    namespace mapping {

        /// \brief Class RapidJSONDecoder
        class RapidJSONDecoder : public ObjectDecoder {
            
        private:
            
            /// \brief Document
            std::shared_ptr<Document> document_;
            
            // Define Json value reference
            Value object_;
                                    
            /// \brief Defauft constructor
            /// \param document JSONDocument
            explicit RapidJSONDecoder(std::shared_ptr<Document> document);
                                                
            /// \brief Defauft constructor
            /// \param document JSONDocument
            /// \param value Object value
            explicit RapidJSONDecoder(std::shared_ptr<Document> document, Value && object);
            
        public:
            
            /// \brief Get document form stream
            /// \param stream
            /// \return decoder
            static RapidJSONDecoder get(std::istream & stream);
            
            /// \brief Destructor
            /// Used to close buffer if opened
            ~RapidJSONDecoder();
            
            // Override encode int
            virtual std::optional<int> decodeInt(const std::string & name) override;
            
            // Override encode string
            virtual std::optional<std::string> decodeString(const std::string & name) override;
            
            // Override create new sub object encoder
            virtual std::shared_ptr<ObjectDecoder> subObjectDecoder(const std::string & name) override;
        };
    }
}

#endif // SWARM_MAPPING_RAPIDJSONDECODER_HXX

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

#ifndef SWARM_MAPPING_OBJECTPROVIDER_HXX
#define SWARM_MAPPING_OBJECTPROVIDER_HXX

#include <optional>
#include <string>
#include <memory>

namespace swarm {
    namespace mapping {

        /// \brief Class ObjectEncoder
        struct ObjectEncoder {
            
            /// \brief Encode an int value
            /// \param name Attribute name
            /// \param value Int value
            virtual void encodeInt(const std::string & name, int value) = 0;
            
            /// \brief Encode string value
            /// \param name Attribute name
            /// \param value String value
            virtual void encodeString(const std::string & name, const std::string & value) = 0;
            
            /// \brief Create sub encoder for sub element
            /// \param name Element name
            virtual std::shared_ptr<ObjectEncoder> subObjectEncoder(const std::string & name) = 0;
            
            /// \brief Encode an template value
            /// Used in mapping definition and forward to correct encode* method
            /// \param name Attribute name
            /// \param value Template value
            template<typename T>
            void encode(const std::string & name, const T & value);
            
            virtual ~ObjectEncoder() {}
        };
        
        struct ObjectDecoder {
            
            /// \brief Decode an int value
            /// \param name Attribute name
            /// \return Optional Int value
            virtual std::optional<int> decodeInt(const std::string & name) = 0;
            
            /// \brief Decode string value
            /// \param name Attribute name
            /// \return Optional string value
            virtual std::optional<std::string> decodeString(const std::string & name) = 0;
            
            /// \brief Create sub decoder for sub element
            /// \param name Element name
            virtual std::shared_ptr<ObjectDecoder> subObjectDecoder(const std::string & name) = 0;
            
            /// \brief Decode an template value
            /// Used in mapping definition and forward to correct decode* method
            /// \param name Attribute name
            /// \return Optional template value
            template<typename T>
            std::optional<T> decode(const std::string & name);
            
            virtual ~ObjectDecoder() {}
        };
    }
}

#include "ObjectProvider.txx"

#endif // SWARM_MAPPING_OBJECTPROVIDER_HXX

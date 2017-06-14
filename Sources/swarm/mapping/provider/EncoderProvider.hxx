/*
 * Copyright 2017 Dami <contact@damiengiron.me>
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

#ifndef SWARM_MAPPING_ENCODERPROVIDER_HXX
#define SWARM_MAPPING_ENCODERPROVIDER_HXX

#include <string>

namespace swarm {
    namespace mapping {

        /// \brief Class EncoderProvider
        struct EncoderProvider {
            
            /// \brief Encode an attribute
            /// \param name Attribute name
            /// \param value Attribute value
            template<typename T>
            void encodeAttribute(const std::string & name, const T & value);
            
            /// \brief Encode an element
            /// \param name Element name
            /// \param value Attribute value
            template<typename T>
            void encodeElement(const std::string & name, const T & value);
        };
    }
}

#endif // SWARM_MAPPING_ENCODERPROVIDER_HXX

#include "EncoderProvider.txx"

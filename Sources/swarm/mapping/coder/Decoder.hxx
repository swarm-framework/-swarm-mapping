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

#ifndef SWARM_MAPPING_DECODER_HXX
#define SWARM_MAPPING_DECODER_HXX

#include <memory>
#include <optional>
#include <cxx-log/Logger.hxx>

namespace swarm {
    namespace mapping {

        /// \brief Class Decoder
        template <class Provider>
        class Decoder {
            
        private:
            
            /// \brief Logger
            static const cxxlog::Logger LOGGER;
            
            /// \brief Provider
            Provider & provider_;
            
        public:
            
            /// \brief Decoder with provider implementation
            /// \param provider Provider
            Decoder(Provider & provider) : provider_(provider) {}
            
            // --- Attributes ---
            
            /// \brief Decode an attribute for a key
            /// \param name Attribute name
            /// \return Attribute value
            template <typename T>
            std::optional<T> decodeAttribute(const std::string & name);
            
            // --- Elements ---
            
            /// \brief Decode an element for a key using a mapper
            /// \param mapper Mapper to use
            /// \param name Attribute name
            /// \return Attribute value
            template <class E, typename V>
            std::shared_ptr<V> decodeElement(Mapping<E, Provider, V> & mapper, const std::string name);
        
            /// \brief Decode an element for a key
            /// \param name Attribute name
            /// \return Attribute value
            template <class E, typename V>
            std::shared_ptr<V> decodeElement(const std::string name);
        };
    }
}

#include "Decoder.txx"

#endif // SWARM_MAPPING_DECODER_HXX

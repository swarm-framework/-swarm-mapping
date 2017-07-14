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

#ifndef SWARM_MAPPING_ENCODER_HXX
#define SWARM_MAPPING_ENCODER_HXX

#include <string>
#include <memory>

#include "../Mapping.hxx"
#include <cxxlog/Logger.hxx>

namespace swarm {
    namespace mapping {

        /// \brief Class Encoder
        template <class Provider>
        class Encoder {
            
        private:
            
            /// \brief Logger
            static const cxxlog::Logger LOGGER;
            
            /// \brief Internal provider
            Provider & provider_;
            
        public:
            
            /// \brief Constructor with provider
            /// \param provider Provider
            Encoder(Provider & provider) : provider_(provider) {}
            
            // --- Attributes ---
            
            /// \brief Encode an attribute for a key
            /// \param name Attribute name
            /// \param value Attribute value
            template <typename T>
            void encodeAttribute(const std::string & name, const T & value);
            
            
            /// \brief Encode an attribute for a key
            /// \param name Attribute name
            /// \param value Attribute value
            template <typename T>
            void encodeAttribute(const std::string & name, const std::shared_ptr<const T> value);
            
            // --- Elements ---
            
            /// \brief Encode an element for a key using a mapper
            /// \param mapper Mapper to use
            /// \param name Attribute name
            /// \param value Attribute value
            template <class D, typename V>
            void encodeElement(Mapping<Provider, D, V> & mapper, const std::string name, const V & value);
            
            /// \brief Encode an element for a key using a mapper
            /// \param mapper Mapper to use
            /// \param name Attribute name
            /// \param value Attribute value
            template <class D, typename V>
            void encodeElement(Mapping<Provider, D, V> & mapper, const std::string name, std::shared_ptr<const V> value);
            
            /// \brief Encode an element for a key
            /// \param name Attribute name
            /// \param value Attribute value
            template <class D, typename V>
            void encodeElement(const std::string name, const V & value);
            
            /// \brief Encode an element for a key
            /// \param name Attribute name
            /// \param value Attribute value
            template <class D, typename V>
            void encodeElement(const std::string name, std::shared_ptr<const V> value);
        };
    }
}

#include "Encoder.txx"

#endif // SWARM_MAPPING_ENCODER_HXX

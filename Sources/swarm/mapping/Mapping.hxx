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

#ifndef SWARM_MAPPING_MAPPING_HXX
#define SWARM_MAPPING_MAPPING_HXX


#include <memory>


namespace swarm {
    namespace mapping {
        
        template<class EncoderProvider>
        class Encoder;
        
        template<class DecoderProvider>
        class Decoder;
        
        /// \brief Class DefaultMapping
        template <class EncoderProvider, class DecoderProvider, class Object> 
        struct DefaultMapping {
               
            /// \brief Encode an object
            /// \param encoder Encoder provider
            /// \param o Object to encode
            virtual void encode(Encoder<EncoderProvider> & encoder, const Object & o);

            /// \brief Decode an object
            /// \param decoder Decoder provider
            virtual std::shared_ptr<Object> decode(Decoder<DecoderProvider> &decoder);
            
            /// \brief Destructor
            virtual ~ DefaultMapping();
        };

        
        /// \brief Class Mapping
        template<class EncoderProvider, class DecoderProvider, class Object>
        struct Mapping : public DefaultMapping<EncoderProvider, DecoderProvider, Object> {

        };
    }
}

#include "Mapping.txx"

#endif // SWARM_MAPPING_MAPPING_HXX

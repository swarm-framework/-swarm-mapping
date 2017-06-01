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

#ifndef SWARM_MAPPING_OBJECTDECODER_HXX
#define SWARM_MAPPING_OBJECTDECODER_HXX

#include <memory>
#include <swarm/exception/SwarmException.hxx>

namespace swarm {
    namespace mapping {
        
        struct DecoderProvider;
        
        /// \brief Class ObjectDecoder
        template<class Object>
        class ObjectDecoder {
            
            /// \brief Decode an object using a decoder provider
            /// \param decoder Decoder used to decode object
            /// \return Object decoded
            std::shared_ptr<Object> encode(DecoderProvider & decoder) {
                throw SwarmException{"Unable to find decoder for an object"};
            }
        };
    }
}

#endif // SWARM_MAPPING_OBJECTDECODER_HXX

#include "ObjectDecoder.txx"

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

#ifndef SWARM_MAPPING_DEFAULTMAPPING_HXX
#include "DefaultMapping.hxx"
#endif

namespace swarm {
    namespace mapping {
        
        // Encode an object
        template <class EncoderProvider, class DecoderProvider, class Object> 
        void DefaultMapping<EncoderProvider,DecoderProvider,Object>::encode(Encoder<EncoderProvider> & encoder, const Object & o) {
            throw SwarmException{"Encoder not implemented"};
        }

        // Decode an object
        template <class EncoderProvider, class DecoderProvider, class Object> 
        std::shared_ptr<Object> DefaultMapping<EncoderProvider,DecoderProvider,Object>::decode(Decoder<DecoderProvider> &decoder) {
            throw SwarmException{"Decoder not implemented"};
        }
         
        // Destructor
        template <class EncoderProvider, class DecoderProvider, class Object> 
        DefaultMapping<EncoderProvider,DecoderProvider,Object>::~DefaultMapping() {}
    }
}

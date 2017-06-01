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

#ifndef SWARM_MAPPING_OBJECTENCODER_HXX
#define SWARM_MAPPING_OBJECTENCODER_HXX

namespace swarm {
    namespace mapping {

        struct EncoderProvider;
        
        /// \brief Class ObjectEncoder
        template<class Object>
        struct ObjectEncoder {
            
            /// \brief Encode an object using an encoder provider
            /// \param encoder Encoder used to encode object
            /// \param object Object to encode
            void encode(EncoderProvider & encoder, const Object & object) {
                throw SwarmException{"Unable to find encoder for an object"};
            }
            
            /// \brief Encode an object using an encoder provider
            /// \param encoder Encoder used to encode object
            /// \param object Object to encode
            void encode(EncoderProvider & encoder, const Object & object) {
                if (object) {
                    encode(encoder, *object);
                }
            }
        };
    }
}

#endif // SWARM_MAPPING_OBJECTENCODER_HXX

#include "ObjectEncoder.txx"

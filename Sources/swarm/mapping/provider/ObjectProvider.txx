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
#include "ObjectProvider.hxx"
#endif // SWARM_MAPPING_OBJECTPROVIDER_HXX

#include <swarm/exception/SwarmException.hxx>

namespace swarm {
    namespace mapping {
    
        namespace delegate {
            
            template<typename T>
            struct ObjectProviderDelegate {
                
                void encode(ObjectEncoder & objectEncoder, const std::string & name, const T & value) {
                    throw SwarmException{"Unbale to encode attribute %1%, type not implemented", name};
                }
                
                std::optional<T> decode(ObjectDecoder & objectDecoder, const std::string & name) {
                    throw SwarmException{"Unbale to decode attribute %1%, type not implemented", name};
                }
            };
                
            // --- Int specialisation ---
            
            template<>
            struct ObjectProviderDelegate<int> {
                
                void encode(ObjectEncoder & objectEncoder, const std::string & name, const int & value) {
                    objectEncoder.encodeInt(name, value);
                }
                
                
                std::optional<int> decode(ObjectDecoder & objectDecoder, const std::string & name) {
                    return objectDecoder.decodeInt(name);
                }
            };
               
            // --- String specialisation ---
            
            template<>
            struct ObjectProviderDelegate<std::string> {
                
                void encode(ObjectEncoder & objectEncoder, const std::string & name, const std::string & value) {
                    objectEncoder.encodeString(name, value);
                }
                
                
                std::optional<std::string> decode(ObjectDecoder & objectDecoder, const std::string & name) {
                    return objectDecoder.decodeString(name);
                }
            };
        }
        
        template<typename T>
        void ObjectEncoder::encode(const std::string & name, const T & value) {
            delegate::ObjectProviderDelegate<T>{}.encode(*this, name, value);
        }
        
        template<typename T>
        std::optional<T> ObjectDecoder::decode(const std::string & name) {
            return delegate::ObjectProviderDelegate<T>{}.decode(*this, name);
        }
    }
}

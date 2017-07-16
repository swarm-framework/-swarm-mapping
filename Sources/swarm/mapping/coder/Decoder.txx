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
#include "Decoder.hxx"
#endif

namespace swarm {
    namespace mapping {

        // --- Attributes ---
        
        // Decode an attribute for a key
        template <class Provider>
        template <typename T>
        std::optional<T> Decoder<Provider>::decodeAttribute(const std::string & name) {
            return provider_.template decode<T>(name);
        }
        
        // --- Elements ---
        
        // Decode an element for a key using a mapper
        template <class Provider>
        template <class E, typename V>
        std::shared_ptr<V>  Decoder<Provider>::decodeElement(Mapping<E, Provider, V> & mapper, const std::string name) {
            auto decoderProvider = provider_.subObjectDecoder(name);
            if (decoderProvider) {
                Decoder<Provider> decoder{*decoderProvider};
                return mapper.decode(decoder);
            } else {
                return std::shared_ptr<V>{};
            }
        }
        
        // Decode an element for a key
        template <class Provider>
        template <class E, typename V>
        std::shared_ptr<V>  Decoder<Provider>::decodeElement(const std::string name) {
            Mapping<E, Provider, V> mapping{};
            return decodeElement(mapping, name);
        }
    }
}

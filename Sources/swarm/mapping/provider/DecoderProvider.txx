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
#ifndef SWARM_MAPPING_DECODERPROVIDER_HXX
#include "DecoderProvider.hxx"
#endif

namespace swarm {
    namespace mapping {
    
        // Decode an attribute
        template<typename T> 
        std::shared_ptr<T> DecoderProvider::decodeAttribute(const std::string & name) {
            // FIXME Add log
            return std::shared_ptr<T>{};
        }
        
        // Decode an element
        template<typename T> 
        std::shared_ptr<T> DecoderProvider::decodeElement(const std::string & name) {
            // FIXME Add log
            return std::shared_ptr<T>{};
        }
            
    }
}

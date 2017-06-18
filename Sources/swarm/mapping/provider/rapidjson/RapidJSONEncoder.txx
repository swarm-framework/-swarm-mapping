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

#ifndef SWARM_MAPPING_RAPIDJSONENCODER_HXX
#include "RapidJSONEncoder.hxx"
#endif

#include <swarm/exception/SwarmException.hxx>

#include <rapidjson/ostreamwrapper.h>
#include <rapidjson/writer.h>

namespace swarm {
    namespace mapping {
        
        RapidJSONEncoder::RapidJSONEncoder() {
            document.SetObject();
        }
        
        // Encode rapid JSON value
        void RapidJSONEncoder::encode(const std::string & name, Value value) {
            // explicit parameters
            Value key(name.c_str(), document.GetAllocator()); // copy string name
            document.AddMember(key, value, document.GetAllocator());
        }
        
        template <typename T>
        void RapidJSONEncoder::encode(const std::string & name, const T & value) {
            throw SwarmException{"Not implemented for RapidJSON"};
        }
              
        template <>
        void RapidJSONEncoder::encode(const std::string & name, const int & value) {
            encode(name, Value(value));
        }
                
        void RapidJSONEncoder::write(std::ostream & ostream) {
            OStreamWrapper osw(ostream);
            Writer<OStreamWrapper> writer(osw);
            document.Accept(writer);
        }
    }
}

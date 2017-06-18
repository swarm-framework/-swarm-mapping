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

namespace swarm {
    namespace mapping {

        /// \brief Class Encoder
        template <class Provider>
        class Encoder {
            
        private:
            
            Provider & provider_;
            
        public:
            
            Encoder(Provider & provider) : provider_(provider) {}
            
            template <typename T>
            void encode(const std::string & name, const T &value);
                        
            template <typename T>
            void encode(const std::string & name, const T *value);
                                  
            template <typename T>
            void encode(const std::string & name, const std::shared_ptr<T> value);
        };
    }
}

#include "Encoder.txx"

#endif // SWARM_MAPPING_ENCODER_HXX

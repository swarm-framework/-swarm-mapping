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

#include "RapidJSONDecoder.hxx"

#include <istream>
#include <rapidjson/istreamwrapper.h>
     
namespace swarm {
    namespace mapping {      
        
        // Defauft constructor
        RapidJSONDecoder::RapidJSONDecoder() : RapidJSONDecoder(std::make_shared<Document>()) {
            
        }
                
        // Defauft constructor
        RapidJSONDecoder::RapidJSONDecoder(std::shared_ptr<Document> document) : document_(document) {
            
        }
        
        // Destructor
        RapidJSONDecoder::~RapidJSONDecoder() {
            
        }
        
        // Override encode int
        std::optional<int> RapidJSONDecoder::decodeInt(const std::string & name) {
            
            if (document_->HasMember(name.c_str())) {
                return (*document_)[name.c_str()].GetInt64();
            } else {
                return std::optional<int>{};
            }
        }
        
        // Override encode string
        std::optional<std::string> RapidJSONDecoder::decodeString(const std::string & name) {
            
            if (document_->HasMember(name.c_str())) {
                return (*document_)[name.c_str()].GetString();
            } else {
                return std::optional<std::string>{};
            }
        }
        
        // Override create new sub object encoder
        std::shared_ptr<ObjectDecoder> RapidJSONDecoder::subObjectDecoder(const std::string & name) {
            return std::shared_ptr<ObjectDecoder>{new RapidJSONDecoder{document_}};
        }
        
        /// \brief Read docmument
        void RapidJSONDecoder::read(std::istream & istream) {
            IStreamWrapper isw(istream);
            document_->ParseStream(isw);
        }
    }
}

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
        RapidJSONDecoder RapidJSONDecoder::get(std::istream & istream) {
            auto document = std::make_shared<Document>();
            IStreamWrapper isw(istream);
            document->ParseStream(isw);
            return RapidJSONDecoder{document};
        }
                
        // Defauft constructor
        RapidJSONDecoder::RapidJSONDecoder(std::shared_ptr<Document> document) : document_(document) {
            if (document_->IsObject()) {
                object_ = document_->GetObject();
            }
        }
               
        // Defauft constructor
        RapidJSONDecoder::RapidJSONDecoder(std::shared_ptr<Document> document, Value && object) : document_(document), object_(std::move(object)) {
        }
        
        // Destructor
        RapidJSONDecoder::~RapidJSONDecoder() {
            
        }
        
        // Override encode int
        std::optional<int> RapidJSONDecoder::decodeInt(const std::string & name) {
            
            if (object_.HasMember(name.c_str())) {
                auto & value = object_[name.c_str()];
                if (value.IsInt()) {
                    return value.GetInt();
                }
                if (value.IsInt64()) {
                    return value.GetInt64();
                }
            }
            
            return std::optional<int>{};
        }
        
        // Override encode string
        std::optional<std::string> RapidJSONDecoder::decodeString(const std::string & name) {
            
            if (object_.HasMember(name.c_str())) {
                auto & value = object_[name.c_str()];
                if (value.IsString()) {
                    return value.GetString();
                }
            } 
            
            return std::optional<std::string>{};
        }
        
        // Override create new sub object encoder
        std::shared_ptr<DocumentDecoder> RapidJSONDecoder::subObjectDecoder(const std::string & name) {
            if (object_.HasMember(name.c_str())) {
                auto & value = object_[name.c_str()];
                if (value.IsObject()) {
                    return std::shared_ptr<DocumentDecoder>{new RapidJSONDecoder{document_, value.GetObject()}};
                }
            }
            
            return std::shared_ptr<DocumentDecoder>{};
        }
    }
}

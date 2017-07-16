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

#include <catch/catch.hxx>

#include <swarm/mapping/Mapping.hxx>
#include <swarm/mapping/provider/rapidjson/RapidJSONEncoder.hxx>
#include <swarm/mapping/provider/rapidjson/RapidJSONDecoder.hxx>
#include <sstream>
#include <iostream>

using namespace swarm::mapping;

namespace swarm {

    namespace mapping {
        
        namespace RapidJSON {
            
            struct SubObject {
              std::string name = "subObjectName";  
            };
            
            struct TestSerialization {
                int attr1 = 30;
                SubObject subObject1;
            };
            
            
        }
        
        template<class EncoderProvider, class DecoderProvider>
        struct Mapping<EncoderProvider, DecoderProvider, RapidJSON::SubObject> : public DefaultMapping<EncoderProvider, DecoderProvider, RapidJSON::SubObject> {
            
            /// \brief Encode an object
            /// \param encoder Encoder provider
            /// \param o Object to encode
            virtual void encode(Encoder<EncoderProvider> & encoder, const RapidJSON::SubObject & o) override {
                encoder.template encodeAttribute<std::string>("name", o.name);
            }
            
            /// \brief Decode an object
            /// \param decoder Decoder provider
            virtual std::shared_ptr<RapidJSON::SubObject> decode(Decoder<DecoderProvider> &decoder) override {
                auto object = std::make_shared<RapidJSON::SubObject>();
                auto name = decoder.template decodeAttribute<std::string>("name");
                if (name) {
                    object->name = name.value();
                }
                return object;
            }
            
        };
        
        template<class EncoderProvider, class DecoderProvider>
        struct Mapping<EncoderProvider, DecoderProvider, RapidJSON::TestSerialization> : public DefaultMapping<EncoderProvider, DecoderProvider, RapidJSON::TestSerialization> {
            
            /// \brief Encode an object
            /// \param encoder Encoder provider
            /// \param o Object to encode
            virtual void encode(Encoder<EncoderProvider> & encoder, const RapidJSON::TestSerialization & o) override {
                encoder.template encodeAttribute<int>("attr1", o.attr1);
                
                Mapping<EncoderProvider, DecoderProvider, RapidJSON::SubObject>mapperA{};
                encoder.template encodeElement(mapperA, "subObject1", o.subObject1);
            }
                        
            /// \brief Decode an object
            /// \param decoder Decoder provider
            virtual std::shared_ptr<RapidJSON::TestSerialization> decode(Decoder<DecoderProvider> &decoder) override {
                auto object = std::make_shared<RapidJSON::TestSerialization>();
                auto attr1 = decoder.template decodeAttribute<int>("attr1");
                if (attr1) {
                    object->attr1 = attr1.value();
                }
                
                Mapping<EncoderProvider, DecoderProvider, RapidJSON::SubObject>mapperA{};
                std::shared_ptr<RapidJSON::SubObject> subObject = decoder.template decodeElement(mapperA, "subObject1");
                if (subObject) {
                    object->subObject1 = *subObject;
                }
                return object;
            }
        };
    }
}


TEST_CASE("Rapid JSON encoder", "[rapidjson]") {
    
    RapidJSON::TestSerialization testSerialization{};
    
    testSerialization.attr1 = 15;
    testSerialization.subObject1.name = "testName";
    
    // --- Mapper ---
    
    Mapping<ObjectEncoder, ObjectDecoder, RapidJSON::TestSerialization> mappingTestSerialization{};
    
    // --- Encode ---
    
    RapidJSONEncoder rapidJSONEncoder{};
    
    // Create coder provider
    Encoder<ObjectEncoder> encoder {rapidJSONEncoder};
    
    // Encode object A
    mappingTestSerialization.encode(encoder, testSerialization);
    
    std::stringstream ss;
    
    rapidJSONEncoder.write(ss);
    
    std::cout << ss.str() << std::endl;
    
    // --- Decode ---

    RapidJSONDecoder rapidJSONDecoder = RapidJSONDecoder::get(ss);
    
    Decoder<ObjectDecoder> decoder {rapidJSONDecoder};
    
    auto decoded = mappingTestSerialization.decode(decoder);
    
    REQUIRE(decoded);
    
    REQUIRE(decoded->attr1 == 15);
    REQUIRE(decoded->subObject1.name == "testName");
}

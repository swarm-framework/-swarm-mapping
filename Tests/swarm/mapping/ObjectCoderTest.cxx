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

#include <iostream>

#include <swarm/mapping/Mapping.hxx>
#include <swarm/mapping/DefaultMapping.hxx>
#include "sample/SampleCoder.hxx"

namespace swarm {
    
    namespace test {
        
        struct ObjectA {
            int attr1;
        };
        
        struct ObjectB {
            int attr1;
        };
        
        struct ObjectC {
            std::string str;
        };
    }
    
    namespace mapping {
        
        /// \brief Class Mapping
        template<class EncoderProvider, class DecoderProvider>
        struct Mapping<EncoderProvider, DecoderProvider, test::ObjectA> {
            
            void encode(Encoder<EncoderProvider> & encoder, const test::ObjectA & o) {
                std::cout << "Encode A" << std::endl;
                encoder.encode("attr1", o.attr1);
            }

            std::shared_ptr<test::ObjectA> decode(Decoder<DecoderProvider> &decoder) {
                std::cout << "Decode A" << std::endl;
                auto object = std::make_shared<test::ObjectA>();
                auto r = decoder.template decode<int>("attr1");
                if (r) {
                    object->attr1 = *r;
                }
                return object;
            }
        };
                
        /// \brief Class Mapping
        template<class EncoderProvider, class DecoderProvider>
        struct Mapping<EncoderProvider, DecoderProvider, test::ObjectB> : public DefaultMapping<EncoderProvider, DecoderProvider, test::ObjectB> {
            
            void encode(Encoder<EncoderProvider> & encoder, const test::ObjectB & o) {
                std::cout << "Encode B" << std::endl;
                encoder.encode(" - attr1", o.attr1);
            }
        };
    }
}

using namespace swarm;
using namespace swarm::mapping;
using namespace swarm::test;

TEST_CASE("Object coder", "[object]") {
        
    // Create mapping
    Mapping<SampleEncoder, SampleDecoder, ObjectA> mappingA{};
    Mapping<SampleEncoder, SampleDecoder, ObjectB> mappingB{};
    Mapping<SampleEncoder, SampleDecoder, ObjectC> mappingC{};
    
    // Create objects
    ObjectA objectA{};
    ObjectB objectB{};
    ObjectC objectC{};
    
    // Sample coder
    SampleEncoder sampleEncoder{};
    SampleDecoder sampleDecoder{};
    
    // Create encoder provider
    Encoder<SampleEncoder> encoder {sampleEncoder};

    // Create decoder provider
    Decoder<SampleDecoder> decoder {sampleDecoder};
        
    // Encode object A
    mappingA.encode(encoder, objectA);
    
    // Encode Object B
    mappingB.encode(encoder, objectB);
    
    // Encode Object C
    REQUIRE_THROWS(mappingC.encode(encoder, objectC));
    
    // Decode Object A
    auto rA = mappingA.decode(decoder);
    
    REQUIRE(rA);
    REQUIRE(rA->attr1 == 10);
    
    // Decode Object B
    REQUIRE_THROWS(mappingB.decode(decoder));
    
    // Decode Object C
    REQUIRE_THROWS(mappingC.decode(decoder));
}

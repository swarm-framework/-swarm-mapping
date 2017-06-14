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

#include <swarm/mapping/object/ObjectCoder.hxx>
#include <swarm/mapping/provider/json/JSonEncoder.hxx>
#include <swarm/mapping/provider/json/JSonDecoder.hxx>

namespace swarm {
    
    namespace test {
        
        class ObjectA {
            
        };
        
        class ObjectB {
            
        };
        
        class ObjectC {
            
        };
    }
    
    namespace mapping {
        
        template<>
        struct ObjectCoder<test::ObjectB> {
            
            /// \brief Decode an object using a decoder provider
            /// \param decoder Decoder used to decode object
            /// \return Object decoded
            std::shared_ptr<test::ObjectB> decode(DecoderProvider & decoder) {
                return std::shared_ptr<test::ObjectB>{};
            }
            
            /// \brief Encode an object using an encoder provider
            /// \param encoder Encoder used to encode object
            /// \param object Object to encode
            void encode(EncoderProvider & encoder, const test::ObjectB & object) {
                
            }
        };
        
        template<>
        struct ObjectEncoder<test::ObjectC> {
               
            /// \brief Encode an object using an encoder provider
            /// \param encoder Encoder used to encode object
            /// \param object Object to encode
            void encode(EncoderProvider & encoder, const test::ObjectC & object) {
                
            }
        };
    }
}

using namespace swarm;
using namespace swarm::mapping;
using namespace swarm::test;

TEST_CASE("Object coder", "[object]") {
    
    ObjectCoder<ObjectA> coderA{};
    ObjectCoder<ObjectB> coderB{};
    ObjectCoder<ObjectC> coderC{};
    
    ObjectA objectA{};
    ObjectB objectB{};
    ObjectC objectC{};
    
    JSonEncoder encoder{};
    JSonDecoder decoder{};
    
    REQUIRE_THROWS(coderA.encode(encoder, objectA));
    REQUIRE_THROWS(coderA.decode(decoder));
    
    REQUIRE_NOTHROW(coderB.encode(encoder, objectB));
    REQUIRE_NOTHROW(coderB.decode(decoder));
    
    REQUIRE_NOTHROW(coderC.encode(encoder, objectC));
    REQUIRE_THROWS(coderC.decode(decoder));
    
    REQUIRE(true);
}

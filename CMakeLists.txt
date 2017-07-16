# Set minimum version of CMake.
cmake_minimum_required(VERSION 3.8)

# Set variables:
#   * PROJECT_NAME
#   * PROJECT_VERSION
project(swarm-mapping VERSION 0.1.0)

# Include config
include(Config/config.cmake)

# Include sub projects
find_dependencies(cxx-log)
find_dependencies(swarm-commons)

find_package(RapidJSON QUIET)

# Create targets
add_library(swarm-mapping

    Sources/swarm/mapping/coder/Encoder.hxx Sources/swarm/mapping/coder/Encoder.txx 
    Sources/swarm/mapping/coder/Decoder.hxx Sources/swarm/mapping/coder/Decoder.txx
    
    Sources/swarm/mapping/Mapping.cxx  Sources/swarm/mapping/Mapping.hxx Sources/swarm/mapping/Mapping.txx
)
# Test RapidJSON
if(DEFINED RapidJSON_DIR)
    message(STATUS "Build RapidJSON mapping with ${RapidJSON_DIR}")
    target_sources(swarm-mapping
    
        PRIVATE
        
            Sources/swarm/mapping/provider/rapidjson/RapidJSONEncoder.cxx Sources/swarm/mapping/provider/rapidjson/RapidJSONEncoder.hxx
            Sources/swarm/mapping/provider/rapidjson/RapidJSONDecoder.cxx Sources/swarm/mapping/provider/rapidjson/RapidJSONDecoder.hxx
    )
    
else()
    message(STATUS "Unable to find RapidJSON, mapping disabled")
endif()

# Global includes. Used by all targets
target_include_directories(
    swarm-mapping 
        
    PRIVATE
        ${cxx-log_INCLUDE_DIR}
        ${swarm-commons_INCLUDE_DIR}
)

# Include build
include(Config/build.cmake)

# Include test
add_subdirectory(Tests)

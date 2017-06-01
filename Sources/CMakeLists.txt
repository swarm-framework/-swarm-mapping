
# Add sources files
set (${PROJECT_NAME}_SOURCES
    
    swarm/mapping/object/ObjectEncoder.hxx swarm/mapping/object/ObjectEncoder.txx
    swarm/mapping/object/ObjectDecoder.hxx swarm/mapping/object/ObjectDecoder.txx
    
    swarm/mapping/provider/EncoderProvider.hxx swarm/mapping/provider/EncoderProvider.txx
    swarm/mapping/provider/DecoderProvider.hxx swarm/mapping/provider/DecoderProvider.txx
    
    swarm/mapping/provider/json/JSonEncoder.cxx swarm/mapping/provider/json/JSonEncoder.hxx
    swarm/mapping/provider/json/JSonDecoder.cxx swarm/mapping/provider/json/JSonDecoder.hxx
)

# Set includes
include_directories(
    .                           # Current project
)

# Create library
add_library(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCES})
target_link_libraries(${PROJECT_NAME}
    swarm-commons
)

# Install exec in bin directory
install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

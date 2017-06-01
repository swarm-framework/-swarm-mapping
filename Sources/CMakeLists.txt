
# Add sources files
set (${PROJECT_NAME}_SOURCES
    swarm/Fake.hxx 
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

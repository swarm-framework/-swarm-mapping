
# Include sub projects
find_dependencies(cxx-log)
find_dependencies(swarm-commons)

find_package(RapidJSON_DIR QUIET)

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
        
            Sources/swarm/mapping/provider/rapidjson/RapidJSONEncoder.hxx Sources/swarm/mapping/provider/rapidjson/RapidJSONEncoder.txx
            Sources/swarm/mapping/provider/rapidjson/RapidJSONDecoder.hxx Sources/swarm/mapping/provider/rapidjson/RapidJSONDecoder.txx
    )
else()
    message(STATUS "Unable to find RapidJSON, mapping disabled")
endif()

# Properties of targets

# Add definitions for targets
# Values:
#   * Debug: -DSWARM_MAPPING_DEBUG=1
#   * Release: -DSWARM_MAPPING_DEBUG=0
#   * other: -DSWARM_MAPPING_DEBUG=0
target_compile_definitions(swarm-mapping  PUBLIC "SWARM_MAPPING_DEBUG=$<CONFIG:Debug>")

# Generate headers:
include(GenerateExportHeader)
generate_export_header(swarm-mapping)

# Global includes. Used by all targets
target_include_directories(
    swarm-mapping 
    
    PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/Sources>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>"
        
    PRIVATE
        ${cxx-log_INCLUDE_DIR}
        ${swarm-commons_INCLUDE_DIR}
)

set(config_install_dir "lib/cmake/${PROJECT_NAME}")
set(include_install_dir "include")

set(generated_dir "${CMAKE_CURRENT_BINARY_DIR}/generated")

# Configuration
set(version_config "${generated_dir}/${PROJECT_NAME}ConfigVersion.cmake")
set(project_config "${generated_dir}/${PROJECT_NAME}Config.cmake")
set(targets_export_name "${PROJECT_NAME}Targets")
set(namespace "${PROJECT_NAME}::")

# Include module with fuction 'write_basic_package_version_file'
include(CMakePackageConfigHelpers)

# Configure '<PROJECT-NAME>ConfigVersion.cmake'
# Note: PROJECT_VERSION is used as a VERSION
write_basic_package_version_file(
    "${version_config}" COMPATIBILITY SameMajorVersion
)

# Configure '<PROJECT-NAME>Config.cmake'
# Use variables:
#   * targets_export_name
#   * PROJECT_NAME
configure_package_config_file(
    "cmake/Config.cmake.in"
    "${project_config}"
    INSTALL_DESTINATION "${config_install_dir}"
)

# Targets:
#   * <prefix>/lib/${target}.a
#   * header location after install: <prefix>/include/*.hxx
#   * headers can be included by C++ code `#include <project/*.hxx>`
install(
    TARGETS swarm-mapping
    EXPORT "${targets_export_name}"
    LIBRARY DESTINATION "lib"
    ARCHIVE DESTINATION "lib"
    RUNTIME DESTINATION "bin"
    INCLUDES DESTINATION "${include_install_dir}"
)

# Headers:
#   * Sources/${target}/*.hxx -> <prefix>/include/${target}/*.hxx
install(
    DIRECTORY "Sources/swarm"
    DESTINATION "${include_install_dir}"
    FILES_MATCHING PATTERN "*.[h;t]xx"
)

# Export headers:
#   * ${CMAKE_CURRENT_BINARY_DIR}/${target}_export.h -> <prefix>/include/${target}_export.h
install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/swarm-mapping_export.h"
    DESTINATION "${include_install_dir}"
)

# Config
#   * <prefix>/lib/cmake/${project}/${Target}Config.cmake
install(
    FILES "${project_config}" "${version_config}"
    DESTINATION "${config_install_dir}"
)

# Config
#   * <prefix>/lib/cmake/${project}/${Target}Targets.cmake
install(
    EXPORT "${targets_export_name}"
    NAMESPACE "${namespace}"
    DESTINATION "${config_install_dir}"
)

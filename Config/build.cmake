
# Include sub projects
find_dependencies(cxx-log)
find_dependencies(swarm-commons)

# Create targets
add_library(swarm-mapping

    Sources/swarm/mapping/object/ObjectCoder.hxx Sources/swarm/mapping/object/ObjectCoder.txx
    Sources/swarm/mapping/object/ObjectEncoder.hxx Sources/swarm/mapping/object/ObjectEncoder.txx
    Sources/swarm/mapping/object/ObjectDecoder.hxx Sources/swarm/mapping/object/ObjectDecoder.txx
    
    Sources/swarm/mapping/provider/EncoderProvider.hxx Sources/swarm/mapping/provider/EncoderProvider.txx
    #Sources/swarm/mapping/provider/EncoderProviderFor.hxx Sources/swarm/mapping/provider/EncoderProviderFor.txx
    Sources/swarm/mapping/provider/DecoderProvider.hxx Sources/swarm/mapping/provider/DecoderProvider.txx
    #Sources/swarm/mapping/provider/DecoderProviderFor.hxx Sources/swarm/mapping/provider/DecoderProviderFor.txx
    
    Sources/swarm/mapping/provider/json/JSonEncoder.cxx Sources/swarm/mapping/provider/json/JSonEncoder.hxx
    Sources/swarm/mapping/provider/json/JSonDecoder.cxx Sources/swarm/mapping/provider/json/JSonDecoder.hxx
)

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

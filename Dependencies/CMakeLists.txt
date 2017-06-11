if(EXISTS ${PROJECT_SOURCE_DIR}/Dependencies/cxx-log/CMakeLists.txt)

    if(NOT TARGET cxx-log)
        # Include cxx-log
        add_subdirectory(${PROJECT_SOURCE_DIR}/Dependencies/cxx-log)

        # Include sources
        include_directories(${PROJECT_SOURCE_DIR}/Dependencies/cxx-log/Sources)
    endif()

endif()

if(EXISTS ${PROJECT_SOURCE_DIR}/Dependencies/swarm-commons/CMakeLists.txt)

    if(NOT TARGET swarm-commons)
        # Include swarm-commons
        add_subdirectory(${PROJECT_SOURCE_DIR}/Dependencies/swarm-commons)

        # Include sources
        include_directories(${PROJECT_SOURCE_DIR}/Dependencies/swarm-commons/Sources)
    endif()

endif()

# --- Find Curl package ---

# Find Curl
find_package(CURL REQUIRED)


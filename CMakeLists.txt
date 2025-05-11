cmake_minimum_required(VERSION 3.28)
project("LVProjectTemplate" LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(
    ${PROJECT_NAME}
    
    "src/core/Utility.cpp"
    "src/core/Game.cpp"
    "src/audio/SoundManager.cpp")
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

# Don't link SFML::Main on non-Windows platforms
if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE SFML::Main SFML::System SFML::Window SFML::Graphics SFML::Audio)
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE SFML::System SFML::Window SFML::Graphics SFML::Audio)
endif()

# target_compile_definitions(${PROJECT_NAME} PRIVATE SFML_STATIC)

# Prevent console window on Windows (does not affect Debug mode)
if(MSVC AND CMAKE_BUILD_TYPE STREQUAL "Release")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        WIN32_EXECUTABLE TRUE)
endif()
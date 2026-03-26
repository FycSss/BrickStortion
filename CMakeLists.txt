cmake_minimum_required(VERSION 3.22)
project(Brickstortion VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(JUCE CONFIG QUIET)

if (NOT JUCE_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        juce
        URL https://github.com/juce-framework/JUCE/archive/refs/tags/8.0.2.tar.gz
    )
    FetchContent_MakeAvailable(juce)
endif()

juce_add_plugin(Brickstortion
    COMPANY_NAME "FycSss"
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS FALSE
    COPY_PLUGIN_AFTER_BUILD TRUE
    PLUGIN_MANUFACTURER_CODE Fycs
    PLUGIN_CODE Brik
    FORMATS VST3
    PRODUCT_NAME "Brickstortion"
)

target_sources(Brickstortion PRIVATE
    Source/JuceHeader.h
    Source/PluginProcessor.cpp
    Source/PluginProcessor.h
    Source/PluginEditor.cpp
    Source/PluginEditor.h
    Source/Audio/DistortionEngine.cpp
    Source/Audio/DistortionEngine.h
    Source/Parameters/PluginParameters.cpp
    Source/Parameters/PluginParameters.h
    Source/UI/BrickSlider.cpp
    Source/UI/BrickSlider.h
    Source/UI/Theme.cpp
    Source/UI/Theme.h
)

target_include_directories(Brickstortion PRIVATE Source)

target_compile_definitions(Brickstortion
    PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
)

target_link_libraries(Brickstortion
    PRIVATE
        juce::juce_audio_utils
        juce::juce_dsp
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)

set(BRICKSTORTION_ASSETS_DIR "${CMAKE_SOURCE_DIR}/Assets" CACHE PATH "Path to theme/assets directory")
target_compile_definitions(Brickstortion PRIVATE BRICKSTORTION_ASSETS_DIR="${BRICKSTORTION_ASSETS_DIR}")

install(TARGETS Brickstortion_VST3 DESTINATION .)
install(DIRECTORY Assets/ DESTINATION Assets)

set(CPACK_PACKAGE_NAME "Brickstortion")
set(CPACK_PACKAGE_VENDOR "FycSss")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_FILE_NAME "Brickstortion-${PROJECT_VERSION}-${CMAKE_SYSTEM_NAME}")
set(CPACK_GENERATOR "ZIP")
if (WIN32)
    list(APPEND CPACK_GENERATOR "NSIS")
endif()
include(CPack)

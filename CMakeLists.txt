cmake_minimum_required(VERSION 3.20)
project(xyz-spoofer-final CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Platform-specific settings
if(NOT WIN32)
    message(FATAL_ERROR "This project only supports Windows")
endif()

# Windows 11 SDK Version (22621 is Windows 11 22H2)
set(CMAKE_SYSTEM_VERSION 10.0.22621.0 CACHE STRING "Windows SDK version")
set(WINDOWS_TARGET_PLATFORM_VERSION "10.0.22621.0")

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

# Add source files
set(SOURCES
    xyz.spoofer.final/main.cpp
    xyz.spoofer.final/hwid.cpp
    xyz.spoofer.final/menus.cpp
    xyz.spoofer.final/caches.cpp
    xyz.spoofer.final/spoof/spoof.cpp
    xyz.spoofer.final/spoof/caches.cpp
    xyz.spoofer.final/spoof/cleaner/clean.c
    xyz.spoofer.final/spoof/cleaner/util.c
    xyz.spoofer.final/btfile/bytetofile.cpp
    xyz.spoofer.final/encrypt/md5.cpp
    xyz.spoofer.final/imgui/imgui.cpp
    xyz.spoofer.final/imgui/imgui_demo.cpp
    xyz.spoofer.final/imgui/imgui_draw.cpp
    xyz.spoofer.final/imgui/imgui_widgets.cpp
    xyz.spoofer.final/imgui/imgui_impl_dx9.cpp
    xyz.spoofer.final/imgui/imgui_impl_win32.cpp
)

# Add header files
set(HEADERS
    xyz.spoofer.final/main.h
    xyz.spoofer.final/hwid.h
    xyz.spoofer.final/menus.h
    xyz.spoofer.final/caches.h
    xyz.spoofer.final/spoof/spoof.h
    xyz.spoofer.final/spoof/caches.h
    xyz.spoofer.final/spoof/cleaner/clean.h
    xyz.spoofer.final/spoof/cleaner/util.h
    xyz.spoofer.final/spoof/cleaner/stdafx.h
    xyz.spoofer.final/btfile/bytetofile.hpp
    xyz.spoofer.final/bytes/bytes.hpp
    xyz.spoofer.final/bytes/font.h
    xyz.spoofer.final/bytes/logo.hpp
    xyz.spoofer.final/encrypt/md5.h
    xyz.spoofer.final/encrypt/xor.h
    xyz.spoofer.final/imgui/imconfig.h
    xyz.spoofer.final/imgui/imgui.h
    xyz.spoofer.final/imgui/imgui_internal.h
    xyz.spoofer.final/imgui/imgui_impl_dx9.h
    xyz.spoofer.final/imgui/imgui_impl_win32.h
    xyz.spoofer.final/imgui/imstb_rectpack.h
    xyz.spoofer.final/imgui/imstb_textedit.h
    xyz.spoofer.final/imgui/imstb_truetype.h
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/xyz.spoofer.final
    ${CMAKE_CURRENT_SOURCE_DIR}/xyz.spoofer.final/imgui
    ${CMAKE_CURRENT_SOURCE_DIR}/xyz.spoofer.final/encrypt
    ${CMAKE_CURRENT_SOURCE_DIR}/xyz.spoofer.final/bytes
    ${CMAKE_CURRENT_SOURCE_DIR}/xyz.spoofer.final/btfile
    ${CMAKE_CURRENT_SOURCE_DIR}/xyz.spoofer.final/spoof
    ${CMAKE_CURRENT_SOURCE_DIR}/xyz.spoofer.final/spoof/cleaner
)

# Windows libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    d3d9
    d3dx9
    dxguid
    winmm
    iphlpapi
    wbemuuid
    ole32
    oleaut32
    uuid
)

# Compiler flags for Windows 11
if(MSVC)
    # Windows 11 specific flags
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        UNICODE
        _UNICODE
        _WIN32_WINNT=0x0A00  # Windows 10 and later
        WINVER=0x0A00
        WIN32_LEAN_AND_MEAN
        NOMINMAX
    )
    
    target_compile_options(${PROJECT_NAME} PRIVATE
        /W3
        /WX-
        /permissive-
        /fp:precise
        /EHsc
    )
    
    # Release build optimizations
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Release>:/O2>
        $<$<CONFIG:Release>:/Oi>
        $<$<CONFIG:Release>:/Ot>
    )
    
    # Enable SDL checks
    target_compile_options(${PROJECT_NAME} PRIVATE /sdl)
    
    # Link options
    set_target_properties(${PROJECT_NAME} PROPERTIES
        VS_PLATFORM_TOOLSET "v143"  # Visual Studio 2022 toolset
    )
    
    # Subsystem for GUI application
    set_target_properties(${PROJECT_NAME} PROPERTIES
        WIN32_EXECUTABLE ON
    )
    
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        target_link_options(${PROJECT_NAME} PRIVATE /SUBSYSTEM:WINDOWS)
    endif()
endif()

# Set as 64-bit only
if(CMAKE_SIZEOF_VOID_P EQUAL 4)
    message(FATAL_ERROR "This project requires a 64-bit build (x64)")
endif()

# Print configuration
message(STATUS "Configuration: ${CMAKE_BUILD_TYPE}")
message(STATUS "Platform: ${CMAKE_SYSTEM_NAME}")
message(STATUS "Architecture: ${CMAKE_SIZEOF_VOID_P} bytes")
message(STATUS "Windows SDK Version: ${WINDOWS_TARGET_PLATFORM_VERSION}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")

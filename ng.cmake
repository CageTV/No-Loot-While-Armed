# NoLootWhileArmed.dll on alandtse's CommonLibSSE-NG (Skyrim SE and AE incl. 1.7.x, no VR); included by E:/WorkSpace/ng-build/CMakeLists.txt (see ng_plugin there).
# The repository's own CMake builds against the Color-Glass CommonLibSSE-NG, whose Address Library reader cannot open the version 5 files of Skyrim 1.7.x.
# Header-only dependencies (the commits of cmake/ports): ClibUtil, SKSEMCP and SimpleIni.h sit in ng-build/deps/No-Loot-While-Armed/include
# (ng-build/fetch_header_port.py; SimpleIni.h is copied from a vcpkg tree).
set(_nlwa_deps "E:/WorkSpace/ng-build/deps/No-Loot-While-Armed/include")
if(NOT EXISTS "${_nlwa_deps}/SKSEMCP/utils.hpp" OR NOT EXISTS "${_nlwa_deps}/ClibUtil/singleton.hpp" OR NOT EXISTS "${_nlwa_deps}/SimpleIni.h")
    message(FATAL_ERROR "No-Loot-While-Armed: header dependencies missing in ${_nlwa_deps}")
endif()
ng_plugin(TARGET NoLootWhileArmed NAME NoLootWhileArmed VERSION 2.0.1 AUTHOR "RavenKZP (fork CageTV)" ROOT "${CMAKE_CURRENT_LIST_DIR}"
    SOURCES src/Events.cpp src/plugin.cpp src/Utils.cpp src/FormIDReader.cpp src/Settings.cpp src/Hooks.cpp src/MCP.cpp src/Serialization.cpp src/Animation.cpp
    INCLUDES "${CMAKE_CURRENT_LIST_DIR}/include" "${_nlwa_deps}"
    PCH "${CMAKE_CURRENT_LIST_DIR}/include/PCH.h"
    DEFINES NLWA_NG)

cmake_minimum_required(VERSION 3.28.3)
project(TypeTraits
        VERSION 1.0.0
        DESCRIPTION "A header only for conversion of standard containers"
        HOMEPAGE_URL "https://github.com/kingkybel/TypeTraits")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake-common/cmake")
include(DkybBuildSettings)
include(GNUInstallDirs)
include(CTest)

dkyb_apply_common_settings(CXX_STANDARD 23)
dkyb_update_submodules()

include(${CMAKE_SOURCE_DIR}/cmake-common/cmake/DkybDependency.cmake)
include(${CMAKE_SOURCE_DIR}/cmake-common/cmake/DkybDependencyRegistry.cmake)

# When using cached dependencies from the workflow, manually set the cache paths
dkyb_dependency_cache_root(_cache_root)
list(APPEND CMAKE_PREFIX_PATH "${_cache_root}/gtest/1_17_0/install")
find_package(GTest REQUIRED)

execute_process(
        COMMAND bash -c "printf \"%s\" $(cat /etc/os-release | grep -E \"^ID=[^\\n]*|^VERSION_ID=[^\\n]*\" | cut -f2 -d= | tr -d '\"')"
        OUTPUT_VARIABLE LINUX_VERSION
)
message("Linux version is '${LINUX_VERSION}'")

set(CMAKE_FIND_LIBRARY_PREFIXES lib)
set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
set(BUILD_SHARED_LIBS OFF)
set(CMAKE_EXE_LINKER_FLAGS "-static")

include_directories(
        BEFORE SYSTEM ${CMAKE_SOURCE_DIR}/include
)

add_library(DirectedGraphs INTERFACE)
# Adding the install interface generator expression makes sure that the include
# files are installed to the proper location (provided by GNUInstallDirs)
target_include_directories(
        DirectedGraphs
        INTERFACE $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_compile_features(DirectedGraphs INTERFACE cxx_std_23)

add_subdirectory(test)

set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=* -p ${CMAKE_SOURCE_DIR}/build")

file(GLOB HEADER_FILES ${CMAKE_SOURCE_DIR}/include/*.h)

# Install the header files directly under 'include/dkyb'
install(FILES ${HEADER_FILES}
        DESTINATION include/dkyb)

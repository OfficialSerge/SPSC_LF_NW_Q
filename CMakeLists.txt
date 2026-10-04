# https://www.youtube.com/watch?v=K5Kg8TOTKjU
cmake_minimum_required(VERSION 4.0)
# set project metadata and use c++ as sole project language.
project(
  SPSC_LF_NW 
  DESCRIPTION "A single producer single consumer lock free, no wait queue"
  LANGUAGES CXX
  VERSION 1.0.0 
)

# update git submodules 
include(cmake/UpdateSubmodules.cmake)
# enable ctest so we can run tests from the cli
include(CTest)
# adding this line allows us to call gtest_discover_tests()
include(GoogleTest)
# defines portable install directories such as cmake_install_libdir
include(GNUInstallDirs)
# add dependencies configured in external directory
add_subdirectory(external)

# request c++23 for targets created below
set(CMAKE_CXX_STANDARD 23)

# fail rather than silently falling back to an older c++ standard
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# generate compile_commands.json for compilation-aware tools like vim!
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# this is a header-only target: no library binary will be produced
add_library(spsc_lf_nw INTERFACE)
add_library(spsc::lf_nw ALIAS spsc_lf_nw)

# publish the header and its include directory as usage requirements
target_sources(
  spsc_lf_nw INTERFACE
    FILE_SET HEADERS
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/source/include
    FILES ${CMAKE_CURRENT_SOURCE_DIR}/source/include/spsc.hpp
)

# generate a separate target to check that public headers actually compile on their own
set_target_properties(
  spsc_lf_nw 
  PROPERTIES 
    VERIFY_INTERFACE_HEADER_SETS ON 
    EXPORT_NAME lf_nw # export as spsc::lf_nw rather than spsc::spsc_lf_nw.
)

# install the header and add this target to the named export set.
install(
  TARGETS spsc_lf_nw
  EXPORT spsc_lf_nw
  FILE_SET HEADERS
)

# install a cmake file that recreates spsc::lf_nw for downstream projects.
install(
  EXPORT spsc_lf_nw
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake"
  NAMESPACE spsc:: 
  FILE spsc_lf_nw-config.cmake
)

# build the googletest executable
add_executable(spsc_tests ${CMAKE_CURRENT_SOURCE_DIR}/test/tests.cpp)

# inherit the library's include paths and googletest's main function.
target_link_libraries(
  spsc_tests PRIVATE 
  spsc::lf_nw 
  GTest::gtest_main
)

# tell google test to go look for tests
gtest_discover_tests(spsc_tests)

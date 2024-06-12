cmake_minimum_required(VERSION 3.12)
project("Bits Serialization"
    DESCRIPTION "A library for serializing data at the bit level"
    VERSION 0.0.1)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "$ENV{HOME}/.local")
include_directories("${CMAKE_PREFIX_PATH}/include")

set(CMAKE_VERBOSE_MAKEFILE OFF)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_C_STANDARD 99)

add_library(bitss bit_serialize.c)
add_executable(main main.c)
target_link_libraries(main bitss)

FIND_PATH(CUNIT_INCLUDE_DIR NAMES CUnit/CUnit.h)
MARK_AS_ADVANCED(CUNIT_INCLUDE_DIR)

FIND_LIBRARY(CUNIT_LIBRARY NAMES cunit libcunit cunitlib)
MARK_AS_ADVANCED(CUNIT_LIBRARY)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(CUnit DEFAULT_MSG CUNIT_LIBRARY CUNIT_INCLUDE_DIR)

IF(CUNIT_FOUND)
  enable_testing ()
  add_executable (test_bitss test.c)

  target_link_libraries(test_bitss -L${CMAKE_BINARY_DIR}/lib ${CUNIT_LIBRARY} bitss)
  set_target_properties (test_bitss PROPERTIES LINK_FLAGS -Wl,-L${CUNIT_LIBRARY},-rpath=${CMAKE_BINARY_DIR}/lib)

  add_test (test_basicdsp ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
ENDIF(CUNIT_FOUND)

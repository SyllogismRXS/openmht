cmake_minimum_required (VERSION 2.6)
project (openmht)

set(OPENMHT_VERSION_MAJOR "0")
set(OPENMHT_VERSION_MINOR "0")
set(OPENMHT_VERSION_PATCH "0")
set(OPENMHT_VERSION "${OPENMHT_VERSION_MAJOR}.${OPENMHT_VERSION_MINOR}.${OPENMHT_VERSION_PATCH}")
set(OPENMHT_VERSION_DATE "2012.12.30")

# give OPENMHT 1 series a few more soversions
set(OPENMHT_SOVERSION "00")

set(CMAKE_INSTALL_PREFIX /usr/local)

# fetch all the local directories for generated code
get_filename_component(OPENMHT_LIB_DIR ./lib ABSOLUTE)
get_filename_component(OPENMHT_BIN_DIR ./bin ABSOLUTE)
get_filename_component(OPENMHT_INC_DIR ./include ABSOLUTE)
get_filename_component(OPENMHT_SRC_DIR ./src ABSOLUTE)
get_filename_component(OPENMHT_SHARE_DIR ./share ABSOLUTE)
get_filename_component(OPENMHT_BUILD_DIR ./build ABSOLUTE)
get_filename_component(OPENMHT_SCRIPTS_DIR ./scripts ABSOLUTE)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-g -Wall -std=c++0x")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall") # -fprofile-arcs -ftest-coverage")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall") # -fprofile-arcs -ftest-coverage")

set(EXECUTABLE_OUTPUT_PATH ${OPENMHT_BIN_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OPENMHT_LIB_DIR})

## set the cmake defaults for libraries and binaries
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OPENMHT_LIB_DIR} CACHE PATH 
  "Output directory for the dynamic libraries" )
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OPENMHT_BIN_DIR} CACHE PATH
  "Output directory for the binaries" )
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OPENMHT_LIB_DIR} CACHE PATH 
  "Output directory for the static libraries (archives)" )

########################################################
# Include Munkres
########################################################
include_directories(/usr/local/include/munkres)
include_directories(/usr/local/include/munkres/adapters)

########################################################
# Find Boost
########################################################
find_package(Boost COMPONENTS thread date_time iostreams program_options regex
  filesystem system REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

########################################################
# Find Eigen
########################################################
find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})


#INSTALL(DIRECTORY ${OPENMHT_INC_DIR} DESTINATION ${CMAKE_INSTALL_PREFIX}
#  FILES_MATCHING REGEX .*\\.h|.*\\.proto
#)

#INSTALL(TARGETS ${} 
#  LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
#  PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
#)

install(DIRECTORY ${OPENMHT_LIB_DIR}/ 
  DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
  )

## let cmake know where the headers are
include_directories(${OPENMHT_INC_DIR})

## copy to openmht/include
file(GLOB_RECURSE INCLUDE_FILES RELATIVE ${OPENMHT_SRC_DIR} src/*.h)
foreach(I ${INCLUDE_FILES})
  configure_file(${OPENMHT_SRC_DIR}/${I} ${OPENMHT_INC_DIR}/openmht/${I} @ONLY)
endforeach()

add_subdirectory(src)
add_subdirectory(share)

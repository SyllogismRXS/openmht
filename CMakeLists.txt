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

## let cmake know where the headers are
include_directories(${OPENMHT_INC_DIR})

## copy to openmht/include
file(GLOB_RECURSE INCLUDE_FILES RELATIVE ${OPENMHT_SRC_DIR} src/*.h)
foreach(I ${INCLUDE_FILES})
  configure_file(${OPENMHT_SRC_DIR}/${I} ${OPENMHT_INC_DIR}/openmht/${I} @ONLY)
endforeach()

add_subdirectory(src)
add_subdirectory(share)


###############################################################################
# Installation
# 
###############################################################################
set(PKGCONFIG_INSTALL_ONLY ON CACHE BOOL "Only install pkgconfig file")

if (NOT PKGCONFIG_INSTALL_ONLY)
  set(CMAKE_INSTALL_PREFIX_SHADOW ${CMAKE_INSTALL_PREFIX})
  
  install(DIRECTORY ${OPENMHT_LIB_DIR}/ 
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/openmht
    )

  # Install header files to system
  # The CMakeLists.txt for each library contains the 
  # commands to install the library
  # TODO, since we removed include directory during development builds, we need
  # to add a new rule here to create the include directory before installation.
  INSTALL(
    DIRECTORY ${OPENMHT_INC_DIR} 
    DESTINATION ${CMAKE_INSTALL_PREFIX}
    FILES_MATCHING REGEX .*\\.h|.*\\.proto|.*\\.inl
    )
else()
  # If we are only installing the pkgconfig file, then make the shadow install
  # prefix set to the current directory
  set(CMAKE_INSTALL_PREFIX_SHADOW ${CMAKE_SOURCE_DIR})
endif()

IF(UNIX AND NOT APPLE)
  # - Add each library to LIBS_STRING 
  # OPENMHT_LIBS is a "global" variable that is passed
  # down to each sub directory and every library that is
  # generated in this project appends its name to this
  # variable.
  foreach(I ${OPENMHT_LIBS})
    #get_filename_component(CUR_LIB ${I} NAME)
    #message("------> : Lib")    
    #message(${I})
    set (LIBS_STRING "${LIBS_STRING} -l${I}")    
  endforeach()    

  # - Use the openmht.pc.in file to generate the 
  #     the final openmht.pc file
  configure_file (
    "${CMAKE_MODULE_PATH}/openmht.pc.in" 
    "${OPENMHT_BUILD_DIR}/openmht.pc" 
    @ONLY)

  # - Install the openmht.pc file to lib/pkgconfig
  install (
    FILES "${CMAKE_CURRENT_BINARY_DIR}/openmht.pc"
    DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig"
    )
ENDIF()

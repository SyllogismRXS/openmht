# - Try to find openmht
# Once done, this will define
#
#  openmht_FOUND - system has openmht
#  openmht_INCLUDE_DIRS - the openmht include directories
#  openmht_LIBRARIES - link these to use openmht

include(LibFindMacros)

# Dependencies (forward, required or quietly)
#libfind_package(openmht_SIM openmht)

# Use pkg-config to get hints about paths
libfind_pkg_check_modules(openmht_PKGCONF openmht)

# Include dir
find_path(openmht_INCLUDE_DIR
  NAMES openmht/multi/MHT.h
  PATHS ${openmht_PKGCONF_INCLUDE_DIRS}
)

message("==================================================")
message("openmht_INCLUDE_DIR: ${openmht_INCLUDE_DIR}")
message("openmht_PKGCONF_LIBRARY_DIRS: ${openmht_PKGCONF_LIBRARY_DIRS}")
message("==================================================")

# Find all the relevant openmht libraries
find_library(common_LIBRARY
  NAMES openmht-common
  PATHS ${openmht_PKGCONF_LIBRARY_DIRS}
)

find_library(filter_LIBRARY
  NAMES openmht-filter
  PATHS ${openmht_PKGCONF_LIBRARY_DIRS}
)

find_library(multi_LIBRARY
  NAMES openmht-multi
  PATHS ${openmht_PKGCONF_LIBRARY_DIRS}
)

find_library(sim_LIBRARY
  NAMES openmht-sim
  PATHS ${openmht_PKGCONF_LIBRARY_DIRS}
)

# Set the include dir variables and the libraries and let libfind_process do the rest.
# NOTE: Singular variables for this library, plural for libraries this this lib depends on.
set(openmht_PROCESS_INCLUDES openmht_INCLUDE_DIR )
set(openmht_PROCESS_LIBS 
  common_LIBRARY
  filter_LIBRARY
  multi_LIBRARY
  sim_LIBRARY
)

libfind_process(openmht)

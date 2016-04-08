# openmht
Open Multi-Hypothesis Tracking
================================

Prerequisites
---------------

1. Using Ubuntu package manager:

   $ sudo apt-get install libeigen3-dev libboost-all-dev gnuplot gnuplot-qt pkg-config

2. Obtain, build, and install Munkres Hungarian Assignment Algorithm:
   
   $ git clone https://github.com/saebyn/munkres-cpp.git
   
   Make change to /path/to/munkres-cpp/CMakeLists.txt:
   Add the following to line 27:

   ${PROJECT_SOURCE_DIR}/src/adapters/boostmatrixadapter.h

   $ mkdir build && cd build         
   $ cmake ..
   $ make
   $ sudo make install
   $ sudo ldconfig

3. Build openMHT:

   $ cd /path/to/openmht
   $ ./build.sh
   $ sudo ./build.sh install
   
   By default, this will only install a pkg-config file that points to your
   local git repository. This is necessary because openMHT is currently under
   heavy development.
   
4. Copy the cmake file located at
   /path/to/openmht/cmake/Modules/Findopenmht.cmake to your /cmake/Modules path
   in your cmake project to find and use openMHT easily. You will need to
   include openmht_INCLUDE_DIRS and link to openmht_LIBRARIES.

   include_directories(${openmht_INCLUDE_DIRS})

   target_link_libraries( your_app_name 
     ${openmht_LIBRARIES}
   )    

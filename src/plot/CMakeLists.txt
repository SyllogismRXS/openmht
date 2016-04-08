#--------------------------------------------------------
# Library Creation
#--------------------------------------------------------
SET (LIBRARY_NAME openmht-plot)
SET (LIB_MAJOR 0)
SET (LIB_MINOR 0)
SET (LIB_RELEASE 1)

file( GLOB SRCS *.cpp)
file( GLOB HDRS *.h)

ADD_LIBRARY(${LIBRARY_NAME} SHARED 
  ${SRCS}
  )

#find_package(Boost COMPONENTS system filesystem iostreams REQUIRED)

target_link_libraries(${LIBRARY_NAME} 
  ${Boost_LIBRARIES}  
  )

SET (_soversion ${LIB_MAJOR}.${LIB_MINOR}.${LIB_RELEASE})

set_target_properties(${LIBRARY_NAME} PROPERTIES SOVERSION ${LIB_MAJOR} VERSION ${_soversion})

## Push up the OPENCV_WORKBENCH_LIBS variable
#set(OPENCV_WORKBENCH_LIBS ${OPENCV_WORKBENCH_LIBS} ${LIBRARY_NAME} PARENT_SCOPE)
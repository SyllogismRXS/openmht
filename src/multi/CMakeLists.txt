set( LIBRARY_NAME_1 openmht-multi )

FILE(GLOB SRCS *.cpp)

ADD_LIBRARY( ${LIBRARY_NAME_1} SHARED  
  ${SRCS}
  )

target_link_libraries(${LIBRARY_NAME_1} 
  ${Boost_LIBRARIES}    
  openmht-common
  openmht-filter
  )

# Install
set(OPENMHT_LIBS ${OPENMHT_LIBS} ${LIBRARY_NAME_1} PARENT_SCOPE)
set( LIBRARY_NAME_1 openmht-filter )

FILE(GLOB SRCS *.cpp)

ADD_LIBRARY( ${LIBRARY_NAME_1} SHARED  
  ${SRCS}
  )

target_link_libraries(${LIBRARY_NAME_1} 
  ${Boost_LIBRARIES}    
  )

# Install
set(OPENMHT_LIBS ${OPENMHT_LIBS} ${LIBRARY_NAME_1} PARENT_SCOPE)
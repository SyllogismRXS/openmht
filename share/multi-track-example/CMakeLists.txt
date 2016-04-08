set( APP_NAME multi-track-example)

add_executable(${APP_NAME} 
  main.cpp
  )

target_link_libraries(${APP_NAME} 
  ${Boost_LIBRARIES}
  openmht-common
  openmht-filter
  openmht-multi
  openmht-plot
  )

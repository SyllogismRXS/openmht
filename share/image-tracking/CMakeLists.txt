set( APP_NAME image-tracking)

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

add_subdirectory(common)
add_subdirectory(filter)
add_subdirectory(multi)
add_subdirectory(sim)
add_subdirectory(plot)

# Push up the OPENMHT_LIBS variable
set(OPENMHT_LIBS ${OPENMHT_LIBS} ${LIBRARY_NAME} PARENT_SCOPE)
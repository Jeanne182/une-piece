find_package (Doxygen)

message("CMAKE_DOC_PATH     " ${CMAKE_CURRENT_SOURCE_DIR})
message("DOXYGEN_EXECUTABLE     " ${DOXYGEN_EXECUTABLE})

if(DOXYGEN_FOUND)
  configure_file (${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile-html.cmake ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile-html)
  add_custom_target (html ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile-html)
  message("-- Use 'make html' to generate the documentation")
endif (DOXYGEN_FOUND)

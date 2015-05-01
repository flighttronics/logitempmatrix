
include_directories("${PROJECT_SOURCE_DIR}/${LIBRGBMATRIX_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/${LIBCURLCPP_DIR}/include")
add_library(librgbmatrix STATIC IMPORTED)
set_property(TARGET librgbmatrix PROPERTY IMPORTED_LOCATION "${LIBRGBMATRIX_LIB_DIR}/librgbmatrix.a")
add_library(curlcpp STATIC IMPORTED)
set_property(TARGET curlcpp PROPERTY IMPORTED_LOCATION "${LIBCURLCPP_LIB_DIR}/libcurlcpp.a")

add_executable (logitempmatrix logitempmatrix.cc)
target_link_libraries (logitempmatrix librgbmatrix curlcpp curl pthread m) 

get_directory_property(OUT_VAR LINK_DIRECTORIES)
message(STATUS "DIR: ${OUT_VAR}")
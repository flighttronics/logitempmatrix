
include_directories("rpi-rgb-led-matrix/lib")
add_library(librgbmatrix STATIC IMPORTED)
set_property(TARGET librgbmatrix PROPERTY IMPORTED_LOCATION "${LIBRGBMATRIX_LIB_DIR}/librgbmatrix.a")
add_executable (logitempmatrix logitempmatrix.cc)
target_link_libraries (logitempmatrix librgbmatrix pthread m) 

get_directory_property(OUT_VAR LINK_DIRECTORIES)
message(STATUS "DIR: ${OUT_VAR}")
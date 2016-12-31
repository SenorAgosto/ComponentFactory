# On windows, we're using VLD for memory leak detection
include(${PROJECT_SOURCE_DIR}/_cmake/post_build/VLD_setup.cmake)

MAKE_LIBRARY(ComponentFactory) 

include(${PROJECT_SOURCE_DIR}/_cmake/post_build/VLD_detect.cmake)

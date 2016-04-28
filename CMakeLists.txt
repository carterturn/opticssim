cmake_minimum_required (VERSION 2.8.11)
project (opticssim)

#Local libraries
add_library(vector tsvector.cpp)
add_library(qed photon.cpp clock.cpp vector2d.cpp)
#add_library(object)

add_definitions(--std=c++11) #Cause vectors

#Graphics
if(GRAPHICS)
  add_definitions(-DGRAPHICS=1)
  #OpenGL, GLFW, and FTGL TODO: make platform independant
  include_directories(/usr/include/)
  link_directories(/usr/lib)
  link_directories(/usr/lib64)
endif(GRAPHICS)

#tests
file(GLOB TEST_SOURCES test_*.cpp)
foreach(test_file ${TEST_SOURCES})
  string(REPLACE ".cpp" "" test_name ${test})
  add_executable(${test_name} ${test_file})
  target_link_libraries(${test_name} vector)
  target_link_libraries(${test_name} qed)
#  target_link_libraries(${test_name} object)
  if(GRAPHICS)
    target_link_libraries(${test_name} GL)
    target_link_libraries(${test_name} glfw)
    target_link_libraries(${test_name} ftgl)

  endif(GRAPHICS)
endforeach(test_file ${TEST_SOURCES})

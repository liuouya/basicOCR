cmake_minimum_required(VERSION 3.0.0)

project( ocr )

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIR} )

find_package( Boost 1.55.0 COMPONENTS program_options REQUIRED )

add_executable( ocr
  main.cpp
  Options.cpp
  Gui.cpp
  Ocr.cpp
  KNN/PreprocessorKNN.cpp
  ANN/PreprocessorANN.cpp
  KNN/ClassifierKNN.cpp
  ANN/ClassifierANN.cpp
  DataDIY/DataDIY.cpp
  DataUCI/DataUCI.cpp
  FeatureExtractor.cpp
  )

target_link_libraries( ocr ${OpenCV_LIBS} )
target_link_libraries( ocr ${Boost_LIBRARIES} )

set_property(TARGET ocr PROPERTY CXX_STANDARD 11)
set_property(TARGET ocr PROPERTY CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_DLAGS} -W -Wall -std=c++0x -g")

add_custom_target(run ALL DEPENDS ocr_engine)
add_custom_command ( OUTPUT ocr_engine
  POST_BUILD
  COMMAND rm -f ocr_engine && ln -s ./build/ocr ocr_engine
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} )

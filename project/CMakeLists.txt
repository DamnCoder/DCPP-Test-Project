CMAKE_MINIMUM_REQUIRED(VERSION 3.1)

#[PROJECT_NAME]
PROJECT(DCPPTest)

#[BUILD_TYPE]
SET(CMAKE_BUILD_TYPE Debug)

# Set the output folders where the program will be created
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/../cmake_modules)
SET(EXTERNALS_PATH ${PROJECT_SOURCE_DIR}/../externals)
SET(ASSETS_PATH ${PROJECT_SOURCE_DIR}/../assets)

# C++ Dialect
SET(CMAKE_CXX_STANDARD 11) # C++11...
SET(CMAKE_CXX_STANDARD_REQUIRED ON) #...is required...
SET(CMAKE_CXX_EXTENSIONS OFF) #...without compiler extensions like gnu++11

if(APPLE)
  set(CMAKE_MACOSX_RPATH 1)
  set(CMAKE_SHARED_LIBRARY_CREATE_C_FLAGS "${CMAKE_SHARED_LIBRARY_CREATE_C_FLAGS} -flat_namespace -undefined dynamic_lookup")
  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -undefined dynamic_lookup")
  set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -undefined dynamic_lookup")
endif(APPLE)

#[PRJ_INCLUDE]
INCLUDE_DIRECTORIES(include)
INCLUDE_DIRECTORIES(include/logic)

#[PRJ_SOURCE_FILES]
SET(SOURCES
	src/main.cpp
	src/testgame.cpp
	src/testhfsm.cpp
	src/logic/logictest.cpp
)

#[PRJ_HEADER_FILES]
SET(HEADERS
	include/testgame.h
	include/testhfsm.h
	include/logic/logictest.h
)

# Generate the executable from the sources
ADD_EXECUTABLE(${PROJECT_NAME} ${SOURCES} ${HEADERS})

ADD_SUBDIRECTORY(${EXTERNALS_PATH}/dcpp/project ${PROJECT_BINARY_DIR}/dcpp)
INCLUDE_DIRECTORIES(${EXTERNALS_PATH}/dcpp/project/include)

INCLUDE_DIRECTORIES(${EXTERNALS_PATH}/dcpp/externals/dcpp_signals/project/include)
INCLUDE_DIRECTORIES(${EXTERNALS_PATH}/dcpp/externals/dcpp_math/project/include)
INCLUDE_DIRECTORIES(${EXTERNALS_PATH}/dcpp/externals/stb_image/project/include)
INCLUDE_DIRECTORIES(${EXTERNALS_PATH}/dcpp/externals/rapidjson/project/include)
INCLUDE_DIRECTORIES(${EXTERNALS_PATH}/dcpp/externals/pathie/include)

ADD_DEPENDENCIES(${PROJECT_NAME} DCPP)

TARGET_LINK_LIBRARIES(${PROJECT_NAME}
	DCPP
	pathie-dynamic
)
 
# Set the location for executable installation
INSTALL(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${EXECUTABLE_OUTPUT_PATH})

ADD_CUSTOM_COMMAND(
	TARGET ${PROJECT_NAME} 
	POST_BUILD 
	COMMAND ${CMAKE_COMMAND} 
	-E copy_directory 
	${ASSETS_PATH} ${EXECUTABLE_OUTPUT_PATH}/${CMAKE_BUILD_TYPE}/assets
)
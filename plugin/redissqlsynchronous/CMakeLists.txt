add_definitions(-DTF_DLL)

find_package(Qt5 COMPONENTS Core Network Xml REQUIRED)

if (NOT Qt5_FOUND)
  message(FATAL_ERROR "Qt5 was not found. Consider setting QT5_CMAKE_PATH to the Qt5Config.cmake directory.")
endif()

file(GLOB headers ${PROJECT_SOURCE_DIR}/plugin/redissqlsynchronous/*.h)
file(GLOB srcs ${PROJECT_SOURCE_DIR}/plugin/redissqlsynchronous/*.cpp)

add_library(RDSSync SHARED
  ${srcs} ${headers}
)
target_include_directories(RDSSync PUBLIC
  ${Qt5Core_INCLUDE_DIRS}
  ${Qt5Network_INCLUDE_DIRS}
  ${Qt5Xml_INCLUDE_DIRS}
  ${TreeFrog_INCLUDE_DIR}
  ${PROJECT_SOURCE_DIR}/helpers
  ${PROJECT_SOURCE_DIR}/models
)
target_link_libraries(RDSSync
  Qt5::Core
  Qt5::Network
  Qt5::Xml
  ${TreeFrog_LIB}
  helper
  model
)
set_target_properties(RDSSync PROPERTIES
  LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/plugin/lib
  ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/plugin/lib
  ARCHIVE_OUTPUT_DIRECTORY_DEBUG   ${PROJECT_SOURCE_DIR}/plugin/lib
  RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/plugin/lib
  RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${PROJECT_SOURCE_DIR}/plugin/lib
  SOVERSION 1.0
)

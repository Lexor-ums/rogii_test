cmake_minimum_required(VERSION 3.5)

project(rogii_test LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_BUILD_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_BUILD_FILES_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(CMAKE_BUILD_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)


# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt5 COMPONENTS Core Quick LinguistTools REQUIRED)

set(TS_FILES rogii_test_ru_RU.ts)
set(QML_IMPORT_PATH ${CMAKE_SOURCE_DIR}/imports ${CMAKE_BINARY_DIR}/imports CACHE STRING "" FORCE)
include_directories(src/models/
    src/ui/
    src/network
    src/data)
if(ANDROID)
    add_library(rogii_test SHARED
      main.cpp
      qml.qrc
    )
else()
    add_executable(rogii_test WIN32
      main.cpp
      src/ui/UIController.cpp
      src/models/UserListModel.cpp
      src/models/UserListItem.cpp
      src/network/ClientImitator.cpp
      src/data/MessageRepository.cpp
      src/data/Message.cpp
      src/network/Sesrver.cpp
      qml.qrc
      img.qrc
      ${TS_FILES}
    )
endif()

target_compile_definitions(rogii_test
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(rogii_test
  PRIVATE Qt5::Core Qt5::Quick)


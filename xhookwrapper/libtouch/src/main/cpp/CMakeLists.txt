# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.18.1)

# Declares and names the project.

project("touch")

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
        touch

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        touch.cpp)

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
        touch

        # Links the target library to the log library
        # included in the NDK.
        ${log-lib})

# 声明一个变量 JNI_LIBS_DIR  并且赋值
# ${CMAKE_SOURCES_DIR} 是 cmake 自带的参数，可以直接使用
set(JNI_LIBS_DIR ${CMAKE_SOURCES_DIR}/src/main/jniLibs)

# 1、添加一个库，在这里可以理解为声明了一个变量，来承载需要引入的库
add_library(
        xhook # 表示的是模块名称，可以自己任意取，例如：deviceutil
        SHARED # 这个是固定的，基本上表示共享库
        IMPORTED # 这个也基本上是固定的，表示当前是导入的，跟我们 java 的 import 差不多含义
)

# 2、将第一步声明的库名称(libraryname)，跟具体的库关联到一起
set_target_properties(
        xhook # 库的名称
        PROPERTIES IMPORTED_LOCATION # 表示当前库是导入的方式
        ${JNI_LIBS_DIR}/${ANDROID_ABI}/libxhook.so # so 动态库的具体路径
)
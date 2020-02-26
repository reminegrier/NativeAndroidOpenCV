# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

#import opencv

#set( ENV{OPENCV_PATH} /home/renault/dev/opencv/android_build_armeabi_v7a/out/sdk/native )
#set( ENV{OPENCV_PATH} /home/renault/dev/opencv/android_build_arm64-v8a/out/sdk/native )
set( ENV{OPENCV_PATH} /home/renault/dev/opencv/android_build_x86/out/sdk/native )

include_directories(SYSTEM $ENV{OPENCV_PATH}/jni/include/ )

add_library( cv_core-lib SHARED IMPORTED)
set_target_properties( cv_core-lib
        PROPERTIES IMPORTED_LOCATION
        $ENV{OPENCV_PATH}/libs/${ANDROID_ABI}/libopencv_core.so )

add_library( cv_imgproc-lib SHARED IMPORTED)
set_target_properties( cv_imgproc-lib
        PROPERTIES IMPORTED_LOCATION
        $ENV{OPENCV_PATH}/libs/${ANDROID_ABI}/libopencv_imgproc.so )

add_library( cv_imgcodecs-lib SHARED IMPORTED)
set_target_properties( cv_imgcodecs-lib
        PROPERTIES IMPORTED_LOCATION
        $ENV{OPENCV_PATH}/libs/${ANDROID_ABI}/libopencv_imgcodecs.so )

add_library( cv_calib3d-lib SHARED IMPORTED)
set_target_properties( cv_calib3d-lib
        PROPERTIES IMPORTED_LOCATION
        $ENV{OPENCV_PATH}/libs/${ANDROID_ABI}/libopencv_calib3d.so )


find_library( jnigraphics-lib jnigraphics )



# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
        my-lib

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        my-lib.cpp)

add_library( # Sets the name of the library.
        native-lib

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        native-lib.cpp)



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
        my-lib

        # Links the target library to the log library
        # included in the NDK.
        ${log-lib}

        #opencv
        ${jnigraphics-lib}
        cv_core-lib
        cv_imgproc-lib
        cv_imgcodecs-lib
        cv_calib3d-lib
        )


target_link_libraries( # Specifies the target library.
        native-lib

        # Links the target library to the log library
        # included in the NDK.
        ${log-lib}

        #opencv
        ${jnigraphics-lib}
        cv_core-lib
        cv_imgproc-lib
        cv_imgcodecs-lib
        cv_calib3d-lib
        )

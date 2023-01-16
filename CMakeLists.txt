cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

project(QSpectrogram VERSION 1.0.0 LANGUAGES CXX CUDA)


find_package(CUDAToolkit)
find_package(Qt5 COMPONENTS Core Widgets CONFIG REQUIRED)

set(SRC
    qspectrogram.cpp
    spectrogram.cpp
    fftcuda.cu
    inputthread.cpp
)

set(INC
    fftcuda.h
    qspectrogram.h
    qspectrogram_global.h
    spectrogram.h
    inputthread.h
)

add_library(lib${PROJECT_NAME} SHARED ${SRC} ${INC})
target_link_libraries(lib${PROJECT_NAME} PUBLIC CUDA::cufft)
target_link_libraries(lib${PROJECT_NAME} PUBLIC Qt5::Core Qt5::Widgets)
target_include_directories(lib${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_compile_definitions(lib${PROJECT_NAME} PRIVATE QSPECTROGRAM_LIB)


add_executable(${PROJECT_NAME} myMain.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE lib${PROJECT_NAME})

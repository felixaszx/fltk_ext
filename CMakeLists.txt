cmake_minimum_required(VERSION 3.20.0)
project(fl_ext VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS off)

add_executable(fl_ext_test "src/test/main.cxx")
target_include_directories(fl_ext_test PUBLIC "include")
target_link_libraries(fl_ext_test fltk fltk_gl glew32 opengl32)

set(FL_APPS task_mgr)

foreach(PROJECT IN LISTS FL_APPS)
    file(GLOB_RECURSE SRC "src/${PROJECT}/*.cxx")
    add_executable("fl_${PROJECT}" ${SRC})
    target_include_directories("fl_${PROJECT}" PUBLIC "include")
    target_include_directories("fl_${PROJECT}" PUBLIC "src/${PROJECT}/include")
    target_link_libraries("fl_${PROJECT}" fltk)

    if(PROJECT MATCHES music)
        target_link_libraries("fl_${PROJECT}" sndfile portaudio tag)
    endif()

    if(PROJECT MATCHES task_mgr)
        target_link_libraries("fl_${PROJECT}")
    endif()
endforeach()

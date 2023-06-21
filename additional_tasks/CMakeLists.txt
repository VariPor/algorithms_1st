cmake_minimum_required(VERSION 3.10)

project(additional_tasks)

file(GLOB_RECURSE tasks_dirs LIST_DIRECTORIES true ".")

MESSAGE("dirs: ${task_dirs}")

foreach(dir ${tasks_dirs})
    IF(IS_DIRECTORY ${dir})
        IF(NOT ${dir} MATCHES ".*src.*")
            MESSAGE("additional task: ${dir}")
            add_subdirectory(${dir})
        ENDIF()
    ELSE()
        CONTINUE()
    ENDIF()
endforeach()

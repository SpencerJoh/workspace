project(RS485_Jisoo C)
set(make_target "RS485_Jisoo")

include(${ROOT_BUILD_PATH}/espf.cmake)

add_library(${make_target} STATIC
    "src/CM.c"
)

target_include_directories(${make_target} PUBLIC ${module_includes} ${CMAKE_CURRENT_SOURCE_DIR}/inc PRIVATE ${ROOT_INCLUDES})
target_compile_definitions(${make_target} PRIVATE ${ROOT_COMPILE_DEFS})
target_compile_options(${make_target} PRIVATE ${ROOT_COMPILE_OPTIONS})
target_link_options(${make_target} PRIVATE ${ROOT_LINK_OPTIONS})
target_link_libraries(${make_target} PRIVATE libtrace assertions)
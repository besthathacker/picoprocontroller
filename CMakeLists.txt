cmake_minimum_required(VERSION 3.13)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(pico_switch_multi_dpad)

pico_sdk_init()

add_executable(pico_switch_multi_dpad
    main.c
    usb_descriptors.c
)

target_include_directories(pico_switch_multi_dpad PRIVATE ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(pico_switch_multi_dpad pico_stdlib tinyusb_device tinyusb_board)

pico_add_extra_outputs(pico_switch_multi_dpad)

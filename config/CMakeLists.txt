# Copyright (c) 2024 The ZMK Contributors
# SPDX-License-Identifier: MIT

if(CONFIG_ZMK_RGB_PER_KEY)
    # Add RGB LED driver sources
    zephyr_library_sources(drivers/led/ws2812.c)
    zephyr_library_sources(src/rgb_led/rgb_led.c)
    
    # Add include directories
    zephyr_include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
endif()

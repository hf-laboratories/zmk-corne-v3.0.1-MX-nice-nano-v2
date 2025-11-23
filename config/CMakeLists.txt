# Copyright (c) 2024 The ZMK Contributors
# SPDX-License-Identifier: MIT

# Add DTS root to find bindings
list(APPEND DTS_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/dts)

if(CONFIG_ZMK_RGB_PER_KEY)
    # Add RGB LED driver sources
    target_sources(app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/drivers/led/ws2812.c)
    target_sources(app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/rgb_led/rgb_led.c)
    
    # Add include directories
    target_include_directories(app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
endif()

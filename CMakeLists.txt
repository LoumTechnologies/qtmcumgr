cmake_minimum_required(VERSION 3.28)
project(qtmcumgr)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "C:/Qt/6.7.0/msvc2019_64/lib/cmake")

find_package(Qt6 COMPONENTS
        Core
        Bluetooth
        REQUIRED)

add_executable(qtmcumgr main.cpp
        Discoverer.cpp
        Discoverer.h
        IoThread.cpp
        IoThread.h
        IoThreadManager.cpp
        IoThreadManager.h
        crc16.cpp
        crc16.h
        smp_group_stat_mgmt.cpp
        smp_group_stat_mgmt.h
        smp_group_zephyr_mgmt.cpp
        smp_group_zephyr_mgmt.h
        smp_bluetooth.cpp
        smp_bluetooth.h
        smp_error.cpp
        smp_error.h
        smp_group.h
        smp_group_array.h
        smp_group_fs_mgmt.cpp
        smp_group_fs_mgmt.h
        smp_group_img_mgmt.cpp
        smp_group_img_mgmt.h
        smp_group_os_mgmt.cpp
        smp_group_os_mgmt.h
        smp_group_settings_mgmt.cpp
        smp_group_settings_mgmt.h
        smp_group_shell_mgmt.cpp
        smp_group_shell_mgmt.h
        smp_processor.cpp
        smp_processor.h
        smp_transport.h
        smp_uart.cpp
        smp_uart.h
        smp_udp.cpp
        smp_udp.h
        smp_message.cpp
        smp_message.h
        Connection.cpp
        Connection.h
        API.cpp
        API.h
        CommonParameters.cpp
        CommonParameters.h
)
target_link_libraries(qtmcumgr
        Qt::Core
        Qt::Bluetooth
)

find_package(Qt6 REQUIRED COMPONENTS Bluetooth)

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()

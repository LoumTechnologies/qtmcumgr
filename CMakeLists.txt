cmake_minimum_required(VERSION 3.28)
project(qtmcumgr)

set(CMAKE_PREFIX_PATH "C:\\Qt\\6.7.0\\msvc2019_64")
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS
        Core
        Bluetooth
        REQUIRED)

add_executable(qtmcumgr
        main.cpp

        IoThread.cpp
        IoThread.h
        IoThreadManager.cpp
        IoThreadManager.h

        API.h
        crc16.cpp
        crc16.h

        CommonParameters.cpp
        CommonParameters.h

        smp_message.h
        smp_processor.h
        smp_transport.h
        smp_uart.h
        smp_udp.h
        BluetoothDeviceManager.h
        CommandEventTcpServer.h
        CommandProcessor.h
        Connection.h
        smp_bluetooth.h
        smp_error.h
        smp_group.h
        smp_group_array.h
        smp_group_fs_mgmt.h
        smp_group_img_mgmt.h
        smp_group_os_mgmt.h
        smp_group_settings_mgmt.h
        smp_group_shell_mgmt.h
        smp_group_stat_mgmt.h
        smp_group_zephyr_mgmt.h

        smp_group_img_mgmt.cpp
        smp_group_os_mgmt.cpp
        smp_group_settings_mgmt.cpp
        smp_group_shell_mgmt.cpp
        smp_group_stat_mgmt.cpp
        smp_group_zephyr_mgmt.cpp
        smp_message.cpp
        smp_processor.cpp
        smp_uart.cpp
        smp_udp.cpp
        BluetoothDeviceManager.cpp
        CommandEventTcpServer.cpp
        CommandProcessor.cpp
        Connection.cpp
        main.cpp
        smp_bluetooth.cpp
        smp_error.cpp
        smp_group_fs_mgmt.cpp
        BluetoothConnection.cpp
        BluetoothConnection.h
        BluetoothConnection.cpp
        BluetoothConnection.h
        NewBluetoothTransport.cpp
        NewBluetoothTransport.h
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

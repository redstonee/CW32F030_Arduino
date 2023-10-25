cmake_minimum_required(VERSION 3.20)

# Set the toolchain location if using Windows
set(TOOLCHAIN_PREFIX "D:/SDKs/gcc-arm-10-2021.10")

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_LIST_DIR}/toolchain-arm-none-eabi.cmake)

project(fuckCW32)

enable_language(ASM)
enable_language(C)
enable_language(CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# Set the source directories
set(ARDUINO_SYS_DIR ${CMAKE_CURRENT_LIST_DIR}/Arduino/system)
set(ARDUINO_VAR_DIR ${CMAKE_CURRENT_LIST_DIR}/Arduino/variants/CW32F0xx/F030C8T)
set(ARDUINO_CORE_DIR ${CMAKE_CURRENT_LIST_DIR}/Arduino/cores/arduino)
set(HW_SRC_DIR ${ARDUINO_SYS_DIR}/Hardware/src)

set(USER_SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/src)

# Set the include directories
include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

include_directories(${ARDUINO_SYS_DIR}/Hardware/inc)
include_directories(${ARDUINO_SYS_DIR}/CMSIS/Core/Include)
include_directories(${ARDUINO_CORE_DIR})
include_directories(${ARDUINO_CORE_DIR}/avr)
include_directories(${ARDUINO_CORE_DIR}/cw32)




# Add source files
set (HW_SRCS
        ${HW_SRC_DIR}/cw32f030_adc.c
        ${HW_SRC_DIR}/cw32f030_atim.c
        ${HW_SRC_DIR}/cw32f030_adc.c
        ${HW_SRC_DIR}/cw32f030_atim.c
        ${HW_SRC_DIR}/cw32f030_awt.c
        ${HW_SRC_DIR}/cw32f030_btim.c
        ${HW_SRC_DIR}/cw32f030_crc.c
        ${HW_SRC_DIR}/cw32f030_debug.c
        ${HW_SRC_DIR}/cw32f030_digitalsign.c
        ${HW_SRC_DIR}/cw32f030_dma.c
        ${HW_SRC_DIR}/cw32f030_flash.c
        ${HW_SRC_DIR}/cw32f030_gpio.c
        ${HW_SRC_DIR}/cw32f030_gtim.c
        ${HW_SRC_DIR}/cw32f030_i2c.c
        ${HW_SRC_DIR}/cw32f030_iwdt.c
        ${HW_SRC_DIR}/cw32f030_lvd.c
        ${HW_SRC_DIR}/cw32f030_pwr.c
        ${HW_SRC_DIR}/cw32f030_ram.c
        ${HW_SRC_DIR}/cw32f030_rcc.c
        ${HW_SRC_DIR}/cw32f030_rtc.c
        ${HW_SRC_DIR}/cw32f030_spi.c
        ${HW_SRC_DIR}/cw32f030_systick.c
        ${HW_SRC_DIR}/cw32f030_uart.c
        ${HW_SRC_DIR}/cw32f030_vc.c
        ${HW_SRC_DIR}/cw32f030_wwdt.c
        ${HW_SRC_DIR}/system_cw32f030.c
        ${HW_SRC_DIR}/startup_cw32f030.s
        ${HW_SRC_DIR}/interrupts_cw32f030.c
)

set (ARDUINO_VARIANT_SRCS
        ${ARDUINO_SYS_DIR}/Hardware/variants/arduino_cw32f030/variant.cpp
        ${ARDUINO_VAR_DIR}/variant.cpp
        ${ARDUINO_VAR_DIR}/PeripheralPins.c
        ${ARDUINO_VAR_DIR}/generic_clock.c
)

set(ARDUINO_CORE_SRCS
        ${ARDUINO_CORE_DIR}/abi.cpp
        ${ARDUINO_CORE_DIR}/board.c
        ${ARDUINO_CORE_DIR}/HardwareSerial.cpp
        # ${ARDUINO_CORE_DIR}/HardwareTimer.cpp
        ${ARDUINO_CORE_DIR}/hooks.c
        ${ARDUINO_CORE_DIR}/IPAddress.cpp
        ${ARDUINO_CORE_DIR}/itoa.c
        ${ARDUINO_CORE_DIR}/main.cpp
        ${ARDUINO_CORE_DIR}/new.cpp
        ${ARDUINO_CORE_DIR}/pins_arduino.c
        ${ARDUINO_CORE_DIR}/Print.cpp
        ${ARDUINO_CORE_DIR}/RingBuffer.cpp
        ${ARDUINO_CORE_DIR}/Stream.cpp
        ${ARDUINO_CORE_DIR}/Tone.cpp
        ${ARDUINO_CORE_DIR}/USBSerial.cpp
        ${ARDUINO_CORE_DIR}/VirtIOS
        ${ARDUINO_CORE_DIR}/WInterrupts.c
        ${ARDUINO_CORE_DIR}/wiring_analog.c
        ${ARDUINO_CORE_DIR}/wiring_digital.c
        ${ARDUINO_CORE_DIR}/wiring_pulse.c
        ${ARDUINO_CORE_DIR}/wiring_shift.c
        ${ARDUINO_CORE_DIR}/WMath.cpp
        ${ARDUINO_CORE_DIR}/WSerial.cpp
        ${ARDUINO_CORE_DIR}/WString.cpp
        ${ARDUINO_CORE_DIR}/avr/dtostrf.c

)

set (USER_SRCS
        ${USER_SRC_DIR}/fuck.cpp
)

add_executable(${CMAKE_PROJECT_NAME}.elf 
        ${HW_SRCS}
        ${USER_SRCS}
)

add_compile_definitions(
        USE_STDPERIPH_DRIVER
)

set(LD_SCRIPT_PATH ${CMAKE_CURRENT_LIST_DIR}/ldscript.ld)
get_filename_component(LD_SCRIPT_PATH_ABS ${LD_SCRIPT_PATH} ABSOLUTE)

set_target_properties(${CMAKE_PROJECT_NAME}.elf PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        LINK_DEPENDS ${LD_SCRIPT_PATH_ABS}
        LINK_FLAGS "-T \"${LD_SCRIPT_PATH_ABS}\""
)

add_custom_target(
        createBinFile ALL
        ${TOOLCHAIN_PREFIX}/bin/${TOOLCHAIN}-objcopy -Obinary
        "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.elf"
        "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.bin"
        DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.elf
)

add_custom_target(
        showSize ALL
        ${TOOLCHAIN_PREFIX}/bin/${TOOLCHAIN}-size "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.elf"
        DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.elf)
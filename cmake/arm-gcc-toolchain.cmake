set(CMAKE_SYSTEM_NAME Generic)		# Tell CMake that this is an unknown/baremetal device and to not assume any linux libraries or executables etc
set(CMAKE_SYSTEM_PROCESSOR arm)
set(TOOLCHAIN_PREFIX arm-none-eabi)	# Tells CMake to use arm gcc tools

find_program(CMAKE_C_COMPILER	${TOOLCHAIN_PREFIX}-gcc)		# CMake searches the PATH for arm-none-eabi-gcc and tells it to use that gcc rather than the regular gcc compiler
find_program(CMAKE_ASM_COMPILER	${TOOLCHAIN_PREFIX}-gcc)		# Tells CMake to also do this gcc thing for assembly files which is needed for the MCU's startup assembly code
find_program(CMAKE_OBJCOPY		${TOOLCHAIN_PREFIX}-objcopy)	# Helpful to manipulate object files. not super necessary but it can be useful in mid compile
find_program(CMAKE_SIZE			${TOOLCHAIN_PREFIX}-size)		# Lets you inspect how much of the STM32's memory your firmware uses

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)	# Prevent CMake from attempting to link and executable to determine if the compile worked

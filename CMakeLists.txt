cmake_minimum_required(VERSION 3.22)
project(image_editor)

# Gather C source files and headers
file(GLOB_RECURSE C_SOURCES
        solution/src/*.c
        solution/src/processing_errors/*.c
        solution/include/*.h
        solution/include/processing_errors/*.h
        main.c
)

# Set compiler flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -no-pie")

# Create the executable
add_executable(image_editor ${C_SOURCES})

# Add custom command to compile the NASM file
set(ASM_SOURCE solution/asm/sepia_filter.asm)
set(ASM_OBJECT ${CMAKE_CURRENT_BINARY_DIR}/out/build/sepia_filter.o)
add_custom_command(OUTPUT ${ASM_OBJECT}
        COMMAND nasm -f elf64 -Ox -o ${ASM_OBJECT} ${ASM_SOURCE}
        DEPENDS ${ASM_SOURCE}
        COMMENT "Assembling ${ASM_SOURCE}")

# Add the assembly object file to the executable
target_sources(image_editor PRIVATE ${ASM_OBJECT})

# Include directories for header files
target_include_directories(image_editor PRIVATE solution/include solution/src solution/asm)
cmake_minimum_required(VERSION 2.8)
project(bpf-learn C)

# we don't build shared libs, so set a special path (due to BPF_BUILD() macro)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/libs-unused")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")
set(BPF_BUILD_PATH "${CMAKE_CURRENT_BINARY_DIR}/bpf-programs")

# Get expected path for the Kernel Headers (running Linux Kernel)
execute_process (
  COMMAND bash -c "uname -r"
  OUTPUT_VARIABLE KERNEL_VER
  )
string(REGEX REPLACE "\n$" "" KERNEL_VER "${KERNEL_VER}")

# Architecture (only tested on x86_64)
execute_process (
  COMMAND bash -c "uname -m"
  OUTPUT_VARIABLE ARCH
  )
string(REGEX REPLACE "\n$" "" ARCH "${ARCH}")
if (${ARCH} STREQUAL "x86_64")
  set(ARCH "x86")
endif()

set(KERNEL_HEADERS "/lib/modules/${KERNEL_VER}/build")

add_subdirectory(bpf-loader)
add_subdirectory(bpf-targets)

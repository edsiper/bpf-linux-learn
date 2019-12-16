# Linux Kernel Headers, tested on Ubuntu 19.10

message(STATUS "Architecture       : ${ARCH}")
message(STATUS "Kernel Headers Path: ${KERNEL_HEADERS}")

#include_directories(
#  "${KERNEL_HEADERS}/arch/${ARCH}/include/generated/uapi"
#  "${KERNEL_HEADERS}/arch/${ARCH}/include/generated"
#  "${KERNEL_HEADERS}/arch/${ARCH}/include"
#  "${KERNEL_HEADERS}/arch/${ARCH}/include/uapi"
#  "${KERNEL_HEADERS}/include"
#  "${KERNEL_HEADERS}/include/uapi"
#  "${KERNEL_HEADERS}/include/generated/uapi"
#  )

include_directories(
  "${KERNEL_HEADERS}/arch/${ARCH}/include/uapi"
  )
set(CMAKE_C_FLAGS "-O2 -target bpf")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -include ${KERNEL_HEADERS}/include/linux/kconfig.h")

# This is a helper macro to build a BPF object file, final targets are
# available on build/bpf-progs/
macro(BPF_BUILD name)
  set(CMAKE_C_FLAGS "-O2 -target bpf")

  # Generate BPF object file, our target
  add_library(${name} OBJECT "${name}.c")

  # This is a dummy step: we want to have our final object file
  # in 'build/bpf-progs' directory, but CMake don't support to
  # run custom commands in a POST_BUILD stage, so the work around
  # is to create an unused shared lib and add a custom command
  # to copy the original BPF object file to the desired path
  set(CMAKE_C_FLAGS "")
  add_library(${name}-unused SHARED "${name}.c")

  add_custom_command(
    TARGET ${name}-unused POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    "${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/${name}.dir/${name}.c.o"
    "${BPF_BUILD_PATH}/${name}.bpf"
    )
endmacro()

BPF_BUILD("bpf-tracepoint-execve")
#add_library("bpf-tracepoint-execve" OBJECT "bpf-tracepoint-execve.c")

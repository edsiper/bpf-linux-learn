set(src
  "bpf_load.c"
  "bpf/bpf.c"
  "bpf-loader.c"
  )

set(CMAKE_C_FLAGS "")
include_directories(".")
#include_directories(include)
include_directories(bpf)
add_executable(bpf-loader ${src})
target_link_libraries(bpf-loader elf)

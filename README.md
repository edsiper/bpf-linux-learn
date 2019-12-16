# BPF Linux Learn	

I am learning about BPF and I found that the _hands-on_ development process is not straightforward if you are out of the Kernel tree. I want to do everything in C language in my local Linux environment. 

The following repository contains a build framework for a BPF program loader and a BPF targets build. The build system is on CMake and tested only on Ubuntu 19.10. 

## Content

The content of the repository is the following:

| Directory                   | description                                                  |
| --------------------------- | ------------------------------------------------------------ |
| [bpf-loader/](bpf-loader/)  | A BPF program loader. This program is an adapted copy from the repository https://github.com/pratyushanand/learn-bpf . Kudos to the real author. |
| [bpf-targets/](bpf-targets) | BPF programs that aims to be loaded in the Kernel. The build process takes every _.c_ file and generate an object with a file name extension _.bpf_ . |

## Requirements

Install the following system dependencies:

```
sudo apt install linux-headers cmake build-essential clang
```

## Build

The build process will build the loader and each BPF kernel program. 

```
$ cd build
$ cmake ../
```

after the build process the binaries will be found at the following locations

- build/bin/
- build/bpf-programs/

## Author

Eduardo Silva <eduardo@monkey.io>

## F.A.Q

### bpf_trace_printk() not working

The first example is not working, the program prints the following output:

```
bpf_load_program() err=22
BPF_STX uses reserved fields
processed 0 insns (limit 1000000) max_states_per_insn 0 total_states 0 peak_states 0 mark_read 0
```

#### root cause 

likely the Kernel don't have KPROBE Events enabled properly, check the Kernel build config with:

```
$ cat /boot/config-`uname -r`|grep KPROBE_EVENTS_ON_NOTRACE
```


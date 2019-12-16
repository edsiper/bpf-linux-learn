/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

#include <stdio.h>
#include "bpf_load.h"

int main(int argc, char **argv)
{
    int ret;
    char *prog;

    prog = argv[1];

    ret = load_bpf_file(argv[1]);
    if (ret != 0) {
        fprintf(stderr, "Kernel could not load BPF program '%s'\n", prog);
        return -1;
    }

    read_trace_pipe();

    return 0;
}

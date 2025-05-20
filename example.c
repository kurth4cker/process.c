// SPDX-License-Identifier: ISC
// SPDX-FileCopyrightText: 2025 kurth4cker <kurth4cker@gmail.com>

#include <stdio.h>
#include <assert.h>

#include "process.h"

int main(void)
{
    Process process = process_run((const char *[]){"cc",  "-fsyntax-only", "main.c"}, 3);
    if (!process.success) {
        fprintf(stderr, "EXAMPLE: cc failed\n");
    }
    process = process_run((const char *[]){"true"}, 1);
    assert(process.success);
    assert(process.started);
    assert(process.exited);
}

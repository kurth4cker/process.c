// SPDX-License-Identifier: ISC
// SPDX-FileCopyrightText: 2025 kurth4cker <kurth4cker@gmail.com>

#ifndef PROCESS_H_INCLUDED
#define PROCESS_H_INCLUDED

#include <stddef.h>
#include <stdbool.h>

typedef struct {
    bool success;
    bool started;
    bool exited;
} Process;
Process process_run(const char **args, size_t count);

#endif // PROCESS_H_INCLUDED

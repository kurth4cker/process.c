// SPDX-License-Identifier: ISC
// SPDX-FileCopyrightText: 2025 kurth4cker <kurth4cker@gmail.com>

#include <stdlib.h>
#include <string.h>

#include "process.h"

#if defined(__unix__) || defined(__APPLE__)
// unix specific
#define _POSIX_C_SOURCE 200809L
#include <unistd.h>
#include <sys/wait.h>

static void execute(const char **args, size_t count) {
    char **execvp_args = malloc(sizeof(*execvp_args) * (count + 1));
    if (execvp_args == NULL) {
        return;
    }
    memcpy(execvp_args, args, count * sizeof(*args));
    execvp_args[count] = NULL;
    execvp(execvp_args[0], execvp_args);
}

Process process_run(const char **args, size_t count)
{
    Process process = { 0 };
    pid_t pid = fork();

    if (pid == -1) {
        return process;
    }
    if (pid == 0) {
        execute(args, count);
        return process;
    }

    int status;
    process.started = true;
    if (waitpid(pid, &status, 0) == -1) {
        return process;
    }
    if (WIFEXITED(status)) {
        process.exited = true;
        process.success =  WEXITSTATUS(status) == 0;
    }
    return process;
    // int execvp(const char *file, char *const argv[]);
}

#elif defined(_WIN32)
Process process_run(const char **args, size_t count)
{
    Process process = {
        .started = false,
        .exited = false,
        .success = false,
    };
    return process;
}
#endif

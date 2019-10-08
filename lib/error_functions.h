//
// Created by 曹子钰 on 2019/10/4.
//

#ifndef LINUX_ERROR_FUNCTIONS_H
#define LINUX_ERROR_FUNCTIONS_H

void errMsg(const char *format, ...);

#ifndef __GNUC__

/* This macro stops 'gcc -Wall' complaining that "control reaches
    end of non-void function" if we use the following functions to
    terminate main() or some other non-void function. */

#define NORETURN __attribute__ ((__noreturn__))
#else
#define NORETURN
#endif

void hello() NORETURN;

void errExit(const char *format, ...) NORETURN;

void err_exit(const char *format, ...) NORETURN;

void errExitEN(int errNum, const char *format, ...) NORETURN;

void fatal(const char *format, ...) NORETURN;

void usageErr(const char *format, ...) NORETURN;

void cmdLineErr(const char *format, ...) NORETURN;

#endif //LINUX_ERROR_FUNCTIONS_H

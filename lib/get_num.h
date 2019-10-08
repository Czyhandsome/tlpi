//
// Created by 曹子钰 on 2019/10/4.
//

#ifndef GET_NUM_H
#define GET_NUM_H

/* Value must be >=0 */
#define GN_NONNEG       01
/* Value must be > 0 */
#define GN_GT_0         02

/* By default, integers are decimal */
/* Can use any base - like strtol(3) */
#define GN_ANY_BASE   0100
/* Value is expressed in octal */
#define GN_BASE_8     0200
/* Value is expressed in hexadecimal */
#define GN_BASE_16    0400


int getInt(const char *arg, int flags, const char *name);

long getLong(const char *arg, int flags, const char *name);

#endif //GET_NUM_H

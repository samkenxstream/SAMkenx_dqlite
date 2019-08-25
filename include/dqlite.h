#ifndef DQLITE_H
#define DQLITE_H

#include <stddef.h>

/* Error codes */
enum { DQLITE_BADSOCKET = 1,
       DQLITE_MISUSE,
       DQLITE_NOMEM,
       DQLITE_PROTO,
       DQLITE_PARSE,
       DQLITE_OVERFLOW,
       DQLITE_EOM,      /* End of message */
       DQLITE_INTERNAL, /* A SQLite error occurred */
       DQLITE_NOTFOUND,
       DQLITE_STOPPED, /* The server was stopped */
       DQLITE_CANTBOOTSTRAP,
       DQLITE_ERROR };

/* Handle connections from dqlite clients */
typedef struct dqlite_task dqlite_task;

int dqlite_task_create(unsigned server_id,
		       const char *advertise_address,
		       const char *data_dir,
		       dqlite_task **t);

void dqlite_task_destroy(dqlite_task *t);

int dqlite_task_set_bind_address(dqlite_task *t, const char *address);

int dqlite_task_get_bind_address(dqlite_task *t, const char **address);

int dqlite_task_set_connect_func(
    dqlite_task *t,
    int (*f)(void *arg, unsigned id, const char *address, int *fd),
    void *arg);

/* Allocate and initialize a dqlite server instance. */
int dqlite_task_start(dqlite_task *t);

/* Stop a dqlite server.
**
** This is a thread-safe API.
**
** In case of error, the caller must invoke sqlite3_free
** against the returned errmsg.
*/
int dqlite_task_stop(dqlite_task *t);

#endif /* DQLITE_H */

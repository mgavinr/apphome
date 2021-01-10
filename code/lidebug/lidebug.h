#ifndef H_LIDEBUGINIT_H
#define H_LIDEBUGINIT_H

#ifndef false
#include <stdbool.h>
#endif
#ifndef LINE_MAX
#define LINE_MAX 4096
#endif
#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE 500
#endif
#include <unistd.h>
#include <sys/types.h>

extern int gv_dbg_fd;
extern char* gv_progname;

#define liDebugEnd() close(g_dbg_fd);

typedef enum {
	RT_INT, RT_CHAR, RT_DOUBLE, RT_FLOAT, RT_LONG, 
	RT_STRING, RT_ADDR, RT_VOID, RT_VOIDPASS, RT_VOIDFAIL
} E_RT_TYPE;

void li_debug_init(char*, char*, bool);
void li_debug_write_header(char*, char*, char*);
void li_debug_func_init(void);

int li_debug_return(E_RT_TYPE a_type, ...);
void DBLOG(const char *string1, ...);
void DBLOGE(const char *string1, ...);
void DBLOGS(const char *string1, ...);
void DBLOGSE(const char *string1, ...);
void DBTRACE(const char *string1, ...);
void DBTRACEE(const char *string1, ...);
void DBENTER(const char *string1, ...);
#define DBVRETURN() li_debug_return(RT_VOID, "");
#define DBPRETURN() li_debug_return(RT_VOIDPASS, "");
#define DBFRETURN() li_debug_return(RT_VOIDFAIL, "");
#define DBRETURN(x) li_debug_return(RT_INT, x);

#ifndef UNUSED
#define UNUSED(x) (void)x;
#endif

#endif

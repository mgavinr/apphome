// TODO: Cleanup to something abit readable
// cpp
#ifdef PYBIND11
#include "pybind11/pybind11.h"
#endif
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include <limits.h>
#include <libgen.h> // basename
#include <time.h>
#include <pthread.h>
// theirs
// mine
#include "lidebug.h"

#define DBG_MASK 	"DBG_MASK"
#define DBG_DIR		"DBG_DIR"

int g_dbg_setting=0;
int gv_dbg_fd=0;
int g_log_fd=0;
char* gv_progname=NULL;
static unsigned g_debug_entercount=0;	
static int g_indent_level=0;
static int g_indent_level_log=0;
static char* g_func_name = NULL;
static char *g_func_list[128];
const char* currentTime();

void li_debug_init(
  char *a_filename,
  char *a_progname,
  bool pid)
{
	char *env_dbgmask;
	char *env_dbgdir;
	char pathname[128];
	char logpathname[128];
	char *path = (char*)"";
	char *pathsep = (char*)"";

    gv_progname = a_progname;
	env_dbgmask = getenv("DBG_MASK");
	if(env_dbgmask == NULL)
		g_dbg_setting = -1; /* stdout */
	else
		g_dbg_setting = atoi(env_dbgmask);


	if(g_dbg_setting >= 0)
	{
		li_debug_func_init();
		env_dbgdir = getenv(DBG_DIR);
		if(env_dbgdir != NULL) path = env_dbgdir;
		
		basename(a_filename);
        if (strlen(path)+strlen(a_filename) > 128-28) {
            fprintf(stderr, "DBG_DIR too large\nexiting\n");
            fflush(stderr);
            exit(0);
        } 
        if (pid) {
		    sprintf(pathname, "%s%s%s_%d%s", path, pathsep, a_filename, getpid(), "");
		    sprintf(logpathname, "%s%s%s_%d%s_evlog", path, pathsep, a_filename, getpid(), "");
        } else {
		    sprintf(pathname, "%s%s%s%s", path, pathsep, a_filename, "");
		    sprintf(logpathname, "%s%s%s%s_evlog", path, pathsep, a_filename, "");
        }

		gv_dbg_fd = open(pathname, O_WRONLY | O_CREAT | O_TRUNC, S_IREAD | S_IWRITE | O_SYNC); 
		if (gv_dbg_fd != -1)
		{
			li_debug_write_header(a_filename, env_dbgdir, env_dbgmask);
            DBTRACE("=THREAD= main");
		}
		else
		{
			fprintf(stdout, "unable to open file [%s]\n", pathname);
		}
		g_log_fd = open(logpathname, O_WRONLY | O_CREAT | O_TRUNC, S_IREAD | S_IWRITE | O_SYNC); 
		if (g_log_fd == -1) g_log_fd = 0;
		
	    if(g_dbg_setting == 0)
		    fprintf(stderr, "DEBUG IS %s (TRUNCATED, OFF, %d)\n", pathname, g_dbg_setting);
        else
		    fprintf(stderr, "DEBUG IS %s (TRUNCATED, ON, %d)\n", pathname, g_dbg_setting);
	} else {
		fprintf(stderr, "DEBUG IS STDOUT (ON,%d) NO LOGFILE\n", g_dbg_setting);
	}
}

int uiDateString(
  char **date_str)
{
    time_t timeval;

    timeval = time( (time_t *) 0);
    *date_str = ctime(&timeval);
    return 0;
}
const char* currentTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    static char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
    return buf;
}

void li_debug_write_header(
  char *a_progname,
  char *a_debug_dir,
  char *a_debug_setting)
{
	static char buffer[LINE_MAX*10*3];
	static int memsetdone = 0;
	char *current_date;

    if(memsetdone == 0) {
	    memset(buffer, 0, sizeof(buffer));
        memsetdone = 1;
    } else {
	    buffer[0] = '\0';
    }
	(void) uiDateString(&current_date);
	
	sprintf(buffer, "%s%s%s%s%s%s%s%s%s", 
		"Enabling debug [", 
		a_progname, 
		"] on ", 
		current_date, 
		"DBG_DIR = [", 
		a_debug_dir, 
		"]\nDBG_MASK = [", 
		a_debug_setting, 
		"]\n\n\0");

	write(gv_dbg_fd, buffer, strlen(buffer));
}

void DBENTER(const char *string1, ...)
{
	int i=0;
	int indent_lvl;
	char *cbuffer;
	static char buffer[LINE_MAX*10*3];
	static char buffer2[LINE_MAX*10+1];
	static int memsetdone = 0;
	va_list stdargs;

    if(memsetdone == 0) {
	    memset(buffer, 0, sizeof(buffer));
	    memset(buffer2, 0, sizeof(buffer2));
        memsetdone = 1;
    } else {
	    buffer[0] = '\0';
	    buffer2[0] = '\0';
    }

	cbuffer = (char*) malloc(strlen(string1)+10);
	memset(cbuffer, 0, strlen(string1)+10);
	while((g_func_list[i] != (char *) 0) && (i<127))
		i++;

	i=0;
	while(string1[i] != '(' && string1[i] != '\0') {
		*(cbuffer+i) = string1[i];
		i++;
	}
	cbuffer[i+1] = '(';
	cbuffer[i+2] = ')';
	cbuffer[i+3] = '\0';


	i=0;	
	g_func_name = cbuffer;
    cbuffer = NULL;
	while((g_func_list[i] != (char *) 0) && (i<127))
		i++;

	g_func_list[i] = g_func_name;

	strcpy(buffer, "");
	sprintf(buffer, "%lu: ", pthread_self());
	indent_lvl = g_indent_level;
	while(indent_lvl > 0)
	{
		strcat(buffer,"    ");
		indent_lvl--;
	}

	strcpy(buffer2, "");
 	va_start(stdargs, string1);                   
  	(void) vsnprintf(buffer2, sizeof(buffer2)-2, string1, stdargs);   
   	va_end(stdargs);                          
	strcat(buffer2,"\0");

	strcat(buffer,buffer2);
    if (true) {
	    char *current_date;
	    (void) uiDateString(&current_date);
	    strcat(buffer," { -- ");
	    strcat(buffer,current_date);
    } else {
	    strcat(buffer," {\n");
    }

	if(g_dbg_setting != 0) {
	    write(gv_dbg_fd, buffer, strlen(buffer));
    }
	g_indent_level+=1;
}

int li_debug_return(E_RT_TYPE a_type, ...)
{
	static char buffer[LINE_MAX*10*3];
	static int memsetdone = 0;
	int i=0;
	va_list stdargs;

    if(memsetdone == 0) {
	    memset(buffer, 0, sizeof(buffer));
        memsetdone = 1;
    } else {
	    buffer[0] = '\0';
    }
	va_start(stdargs, a_type);

	while((g_func_list[i] != (char *) 0) && (i<127))
		i++;
	
	i--;
	if(i<0) return -1;

	g_func_name = g_func_list[i];

	switch(a_type)
	{
		case RT_INT:	
		  sprintf(buffer, "%s%s%s%d", "} ", g_func_name, " -> ", 
		  				(int) va_arg(stdargs, int));
		  break;
		case RT_STRING:
		  sprintf(buffer, "%s%s%s%s", "} ", g_func_name, " -> ", 
		  				(char *) va_arg(stdargs, char*));
		  break;
		case RT_CHAR:
		  sprintf(buffer, "%s%s%s%c", "} ", g_func_name, " -> ", 
		  				(char) va_arg(stdargs, int));
		  break;
		case RT_LONG:
		  sprintf(buffer, "%s%s%s%ld", "} ", g_func_name, " -> ", 
		  				(long) va_arg(stdargs, long));
		  break;
		case RT_ADDR:
		  sprintf(buffer, "%s%s%s%x", "} ", g_func_name, " -> ", 
		  				(int) va_arg(stdargs, int));
		  break;
		case RT_FLOAT:
		  sprintf(buffer, "%s%s%s%f", "} ", g_func_name, " -> ", 
		  				(double) va_arg(stdargs, double));
		  break;
		case RT_VOID:
		  sprintf(buffer, "%s%s%s%s", "} ", g_func_name, " -> ", "<no return>");
		  break;
		case RT_VOIDFAIL:
		  sprintf(buffer, "%s%s%s%s", "} ", g_func_name, " -> ", "<fail return>");
		  break;
		case RT_VOIDPASS:
		  sprintf(buffer, "%s%s%s%s", "} ", g_func_name, " -> ", "<pass return>");
		  break;
		default:
		  sprintf(buffer, "%s%s%s%s","} ", g_func_name, " -> ", "[unknown type]");
		  break;
	};
	g_indent_level-=1;
	DBTRACE(buffer,NULL);

	i=0;
	while((g_func_list[i] != (char *) 0) && (i<127))
		i++;

	i--;
	free(g_func_list[i]);
	g_func_list[i] = (char *) 0;

	va_end(stdargs);
	return 0;
}

// TRACE FILE NORMAL
void DBTRACE(const char *string1, ...)
{
	static char buffer[LINE_MAX*10*3];
	static char buffer2[LINE_MAX*10+1];
	static int memsetdone = 0;
	int indent_lvl;
	va_list stdargs;

    if(memsetdone == 0) {
	    memset(buffer, 0, sizeof(buffer));
	    memset(buffer2, 0, sizeof(buffer2));
        memsetdone = 1;
    } else {
	    buffer[0] = '\0';
	    buffer2[0] = '\0';
    }
	sprintf(buffer, "%lu: ", pthread_self());
	indent_lvl = g_indent_level;
	while(indent_lvl > 0)
	{
		strcat(buffer,"    ");
		indent_lvl--;
	}

	strcpy(buffer2, "");
 	va_start(stdargs, string1);                   
  	(void) vsnprintf(buffer2, sizeof(buffer2)-2, string1, stdargs);   
   	va_end(stdargs);                          
	strcat(buffer2,"\0");

	strcat(buffer,buffer2);
    if (false) {
	    char *current_date;
	    (void) uiDateString(&current_date);
	    strcat(buffer," -- ");
	    strcat(buffer,current_date);
    } else {
	    strcat(buffer,"\n");
    }

	if(g_dbg_setting != 0) {
	    write(gv_dbg_fd, buffer, strlen(buffer));
    }
    g_debug_entercount++;
}

// TRACE FILE ERROR
void DBTRACEE(const char *string1, ...)
{
	static char buffer[LINE_MAX*10*3];
	static char buffer2[LINE_MAX*10+1];
	static int memsetdone = 0;
	int indent_lvl;
	va_list stdargs;

    if(memsetdone == 0) {
	    memset(buffer, 0, sizeof(buffer));
	    memset(buffer2, 0, sizeof(buffer2));
        memsetdone = 1;
    } else {
	    buffer[0] = '\0';
	    buffer2[0] = '\0';
    }
	sprintf(buffer, "%lu:E: ", pthread_self());
	indent_lvl = g_indent_level;
	while(indent_lvl > 0)
	{
		if (indent_lvl == 1) strcat(buffer,"  ");
		else strcat(buffer,"    ");
		indent_lvl--;
	}

	strcpy(buffer2, "");
 	va_start(stdargs, string1);                   
  	(void) vsnprintf(buffer2, sizeof(buffer2)-2, string1, stdargs);   
   	va_end(stdargs);                          
	strcat(buffer2,"\0");

	strcat(buffer,buffer2);
    if (false) {
	    char *current_date;
	    (void) uiDateString(&current_date);
	    strcat(buffer," -- ");
	    strcat(buffer,current_date);
    } else {
	    strcat(buffer,"\n");
    }

	if(g_dbg_setting != 0) {
	    write(gv_dbg_fd, buffer, strlen(buffer));
    }
    g_debug_entercount++;
}

// STDOUT and if there is a logfile goes there too and trace file
void DBLOGP(const char *string1, ...)
{
	static char buffer[LINE_MAX*10*3];
	static char buffer2[LINE_MAX*10+1];
	static int memsetdone=0;
	int indent_lvl;
	va_list stdargs;

    if(memsetdone == 0) {
	    memset(buffer, 0, sizeof(buffer));
	    memset(buffer2, 0, sizeof(buffer2));
        memsetdone = 1;
    } else {
	    buffer[0] = '\0';
	    buffer2[0] = '\0';
    }
	indent_lvl = g_indent_level_log;
	while(indent_lvl > 0)
	{
		strcat(buffer,"    ");
		indent_lvl--;
	}

	strcpy(buffer2, "");
 	va_start(stdargs, string1);                   
  	(void) vsnprintf(buffer2, sizeof(buffer2)-2,string1, stdargs);   
   	va_end(stdargs);                          
	strcat(buffer2,"\0");

	strcat(buffer,buffer2);
    if (false) {
	    char *current_date;
	    (void) uiDateString(&current_date);
	    strcat(buffer," -- ");
	    strcat(buffer,current_date);
    } else {
	    strcat(buffer,"\n");
    }

	fprintf(stdout, "%s", buffer);
	fflush(stdout);
    if (g_log_fd != 0) {
	    write(g_log_fd, buffer, strlen(buffer));
	    write(gv_dbg_fd, buffer, strlen(buffer));
    }
}

// STDOUT STDERR and if there is a log file goes there too and a trace file
void DBLOGPE(const char *string1, ...)
{
	static char buffer[LINE_MAX*10*3];
	static char buffer2[LINE_MAX*10+1];
	static int memsetdone=0;
	int indent_lvl;
	va_list stdargs;

    if(memsetdone == 0) {
	    memset(buffer, 0, sizeof(buffer));
	    memset(buffer2, 0, sizeof(buffer2));
        memsetdone = 1;
    } else {
	    buffer[0] = '\0';
	    buffer2[0] = '\0';
    }
	indent_lvl = g_indent_level_log;
	while(indent_lvl > 0)
	{
		strcat(buffer,"    ");
		indent_lvl--;
	}

	strcpy(buffer2, "");
 	va_start(stdargs, string1);                   
  	(void) vsnprintf(buffer2, sizeof(buffer2)-2,string1, stdargs);   
   	va_end(stdargs);                          
	strcat(buffer2,"\0");

	strcat(buffer,buffer2);
    if (false) {
	    char *current_date;
	    (void) uiDateString(&current_date);
	    strcat(buffer," -- ");
	    strcat(buffer,current_date);
    } else {
	    strcat(buffer,"\n");
    }

	fprintf(stderr, "%s", buffer);
	fflush(stderr);
	fprintf(stdout, "%s", buffer);
	fflush(stdout);
    if (g_log_fd != 0) {
	    write(g_log_fd, buffer, strlen(buffer));
	    write(gv_dbg_fd, buffer, strlen(buffer));
    }
}


// STDOUT and if there is a logfile goes there too, also prints the thread 
void DBLOG(const char *string1, ...)
{
	static char buffer[LINE_MAX*10*3];
	static char buffer2[LINE_MAX*10+1];
	static int memsetdone=0;
	int indent_lvl;
	va_list stdargs;

    if(memsetdone == 0) {
	    memset(buffer, 0, sizeof(buffer));
	    memset(buffer2, 0, sizeof(buffer2));
        memsetdone = 1;
    } else {
	    buffer[0] = '\0';
	    buffer2[0] = '\0';
    }
	sprintf(buffer, "%lu: ", pthread_self());
	indent_lvl = g_indent_level;
	while(indent_lvl > 0)
	{
		strcat(buffer,"    ");
		indent_lvl--;
	}

	strcpy(buffer2, "");
 	va_start(stdargs, string1);                   
  	(void) vsnprintf(buffer2, sizeof(buffer2)-2,string1, stdargs);   
   	va_end(stdargs);                          
	strcat(buffer2,"\0");

	strcat(buffer,buffer2);
    if (false) {
	    char *current_date;
	    (void) uiDateString(&current_date);
	    strcat(buffer," -- ");
	    strcat(buffer,current_date);
    } else {
	    strcat(buffer,"\n");
    }

	fprintf(stdout, "%s", buffer);
	fflush(stdout);
    if (g_log_fd != 0) {
	    write(g_log_fd, buffer, strlen(buffer));
	    write(gv_dbg_fd, buffer, strlen(buffer));
    }
}

// STDOUT STDERR and if there is a logfile goes there too and a trace file, prints :E: 
void DBLOGE(const char *string1, ...)
{
	static char buffer[LINE_MAX*10*3];
	static char buffer2[LINE_MAX*10+1];
	static int memsetdone=0;
	int indent_lvl;
	va_list stdargs;

    if(memsetdone == 0) {
	    memset(buffer, 0, sizeof(buffer));
	    memset(buffer2, 0, sizeof(buffer2));
        memsetdone = 1;
    } else {
	    buffer[0] = '\0';
	    buffer2[0] = '\0';
    }
	sprintf(buffer, "%lu:E: ", pthread_self());
	indent_lvl = g_indent_level;
	while(indent_lvl > 0)
	{
	    if (indent_lvl == 1) {
		  strcat(buffer,"  ");
        } else {
		  strcat(buffer,"    ");
        }
		indent_lvl--;
	}

	strcpy(buffer2, "");
 	va_start(stdargs, string1);                   
  	(void) vsnprintf(buffer2, sizeof(buffer2)-2,string1, stdargs);   
   	va_end(stdargs);                          
	strcat(buffer2,"\0");

	strcat(buffer,buffer2);
    if (false) {
	    char *current_date;
	    (void) uiDateString(&current_date);
	    strcat(buffer," -- ");
	    strcat(buffer,current_date);
    } else {
	    strcat(buffer,"\n");
    }

	fprintf(stderr, "%s", buffer);
	fflush(stderr);
	fprintf(stdout, "%s", buffer);
	fflush(stdout);
    if (g_log_fd != 0) {
	    write(g_log_fd, buffer, strlen(buffer));
	    write(gv_dbg_fd, buffer, strlen(buffer));
    }
}

void li_debug_func_init(void)
{
	int i;
	for(i=0; i<128; i++)
		g_func_list[i] = (char *) 0;
}

#ifdef PYBIND11
PYBIND11_MODULE(lidebuginit, m) {
    m.doc() = "pybind11 example plugin"; // optional module docstring
    m.def("li_debug_init", &li_debug_init, "A function which inits debug");
}
#endif

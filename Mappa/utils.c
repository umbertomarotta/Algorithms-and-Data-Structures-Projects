#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>

#if defined POSIX
  #define CLEARSCR system ( "clear" )
#elif defined MSDOS || defined _WIN32
  #define CLEARSCR system ( "cls" )
#else
  #define CLEARSCR system ( "clear" )
#endif

void aspetta(double secondi){
    time_t tim = time(NULL);
    while(difftime(time(NULL),tim) < secondi);
}

void press_enter(){
    char enter = 0;
     while (enter != '\r' && enter != '\n') { enter = getchar(); }
}

void clear_screen(){
    CLEARSCR;
}

int addThemAll( int numargs, ... ){
    va_list listPointer;
    va_start( listPointer, numargs );

    int sum = 0;
    int i;
    for( i = 0 ; i < numargs; i++ )
    {

        int arg = va_arg( listPointer, int );

        printf( "    The %dth arg is %d\n", i, arg );

        sum += arg;
    }
    printf("--");
    printf("END OF ARGUMENT LIST\n\n");

    va_end( listPointer );

    printf("The total sum was %d\n\n", sum);
    return sum;
}

#define _WIN32_WINNT  0x0501
#if defined(_WIN32)
#include <Windows.h>

#elif defined(__unix__) || defined(__unix) || defined(unix) || (defined(__APPLE__) && defined(__MACH__))
#include <unistd.h>
#include <sys/types.h>
#include <sys/param.h>
#if defined(BSD)
#include <sys/sysctl.h>
#endif

#else
#error "Unable to define getMemorySize( ) for an unknown OS."
#endif

/**
 * Returns the size of physical memory (RAM) in bytes.
 */
size_t getMemorySize( )
{
#if defined(_WIN32) && (defined(__CYGWIN__) || defined(__CYGWIN32__))
	/* Cygwin under Windows. ------------------------------------ */
	/* New 64-bit MEMORYSTATUSEX isn't available.  Use old 32.bit */
	MEMORYSTATUS status;
	status.dwLength = sizeof(status);
	GlobalMemoryStatus( &status );
	return (size_t)status.dwTotalPhys;

#elif defined(_WIN32)
	/* Windows. ------------------------------------------------- */
	/* Use new 64-bit MEMORYSTATUSEX, not old 32-bit MEMORYSTATUS */
	//MEMORYSTATUSEX status;
	MEMORYSTATUSEX status;
	status.dwLength = sizeof(status);
	GlobalMemoryStatusEx( &status );
	return (size_t)status.ullTotalPhys;

#elif defined(__unix__) || defined(__unix) || defined(unix) || (defined(__APPLE__) && defined(__MACH__))
	/* UNIX variants. ------------------------------------------- */
	/* Prefer sysctl() over sysconf() except sysctl() HW_REALMEM and HW_PHYSMEM */

#if defined(CTL_HW) && (defined(HW_MEMSIZE) || defined(HW_PHYSMEM64))
	int mib[2];
	mib[0] = CTL_HW;
#if defined(HW_MEMSIZE)
	mib[1] = HW_MEMSIZE;            /* OSX. --------------------- */
#elif defined(HW_PHYSMEM64)
	mib[1] = HW_PHYSMEM64;          /* NetBSD, OpenBSD. --------- */
#endif
	int64_t size = 0;               /* 64-bit */
	size_t len = sizeof( size );
	if ( sysctl( mib, 2, &size, &len, NULL, 0 ) == 0 )
		return (size_t)size;
	return 0L;			/* Failed? */

#elif defined(_SC_AIX_REALMEM)
	/* AIX. ----------------------------------------------------- */
	return (size_t)sysconf( _SC_AIX_REALMEM ) * (size_t)1024L;

#elif defined(_SC_PHYS_PAGES) && defined(_SC_PAGESIZE)
	/* FreeBSD, Linux, OpenBSD, and Solaris. -------------------- */
	return (size_t)sysconf( _SC_PHYS_PAGES ) *
		(size_t)sysconf( _SC_PAGESIZE );

#elif defined(_SC_PHYS_PAGES) && defined(_SC_PAGE_SIZE)
	/* Legacy. -------------------------------------------------- */
	return (size_t)sysconf( _SC_PHYS_PAGES ) *
		(size_t)sysconf( _SC_PAGE_SIZE );

#elif defined(CTL_HW) && (defined(HW_PHYSMEM) || defined(HW_REALMEM))
	/* DragonFly BSD, FreeBSD, NetBSD, OpenBSD, and OSX. -------- */
	int mib[2];
	mib[0] = CTL_HW;
#if defined(HW_REALMEM)
	mib[1] = HW_REALMEM;		/* FreeBSD. ----------------- */
#elif defined(HW_PYSMEM)
	mib[1] = HW_PHYSMEM;		/* Others. ------------------ */
#endif
	unsigned int size = 0;		/* 32-bit */
	size_t len = sizeof( size );
	if ( sysctl( mib, 2, &size, &len, NULL, 0 ) == 0 )
		return (size_t)size;
	return 0L;			/* Failed? */
#endif /* sysctl and sysconf variants */

#else
	return 0L;			/* Unknown OS. */
#endif
}

void feature_segreta(){
    printf("\nKING IL CAVALIERE IMPEDISCE\nOGNI INPUT ILLEGALE\n\n");
    printf("                  {}\n");
    printf("  ,   A           {}\n");
    printf(" / \\, | ,        .--.\n");
    printf("|  =|= >        /.--.\\\n");
    printf(" \\ /` | `       |====|\n");
    printf("  `   |         |`::`|\n");
    printf("      |     .-;`\\..../`;_.-^-._\n");
    printf("     /\\\\/  /  |...::..|`   :   `|\n");
    printf("     |:'\\ |   /'''::''|   .:.   |\n");
    printf("      \\ /\\;-,/\\   ::  |..ASCII..|\n");
    printf("      |\\ <` >  >._::_.| ':ART:' |\n");
    printf("      | `""`_/   ^^/>/>  |   ':'   |\n");
    printf("      |       |       \\    :   /\n");
    printf("      |       |        \\   :   /\n");
    printf("      |       |___/\\___|`-.:.-`\n");
    printf("      |        \\_ || _/    `\n");
    printf("      |        <_ >< _>\n");
    printf("      |        |  ||  |\n");
    printf("      |        |  ||  |\n");
    printf("      |       _\\.:||:./_\n");
    printf("      |      /____/\\____\\\n");
    printf("\n");
}


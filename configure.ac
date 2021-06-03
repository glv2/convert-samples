AC_INIT(convert-samples, 1.0.0)
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR(convert-samples.c)

dnl Check for toolchain and install components
AC_PROG_CC
AC_PROG_INSTALL

dnl Check for standard headers
AC_CHECK_HEADERS([complex.h math.h stdio.h strings.h])

dnl Check for functions
AC_CHECK_FUNCS([printf fprintf])
AC_CHECK_FUNCS([fopen fclose])
AC_CHECK_FUNCS([strcasecmp])
AC_CHECK_FUNCS([getopt])

dnl Check for libraries
AC_CHECK_LIB(m, crealf, [], AC_MSG_ERROR([math library required]))

AC_CONFIG_FILES(Makefile)
AC_OUTPUT

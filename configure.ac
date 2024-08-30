AC_INIT([c_serialization], [0.1.0], [lincketheo.dev@gmail.com])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])
AC_PROG_CC
AC_PROG_LIBTOOL

AC_ARG_WITH([cunit],
            [AS_HELP_STRING([--without-cunit], [build without CUnit tests])],
            [with_cunit=$withval], [with_cunit=yes])

if test "x$with_cunit" != "xno"; then
  
AC_CONFIG_FILES([Makefile])
AC_OUTPUT

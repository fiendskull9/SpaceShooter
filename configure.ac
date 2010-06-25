#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.65])
AC_INIT([SpaceShooter], [2.3], [al3xbio@gmail.com])
AC_CONFIG_SRCDIR([src/SpaceShooter.c])
#AC_CONFIG_HEADER([src/SpaceShooter.h])

AM_PATH_ALLEGRO([4.2.2])

AM_INIT_AUTOMAKE([SpaceShooter], [2.3])

# Checks for programs.
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_LN_S

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h])
AC_CHECK_HEADERS([allegro.h])
AC_CHECK_HEADERS([sys/stat.h])
AC_CHECK_HEADERS([sys/types.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_CHECK_FUNCS([mkdir])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT

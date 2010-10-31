#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

m4_define([version_major], [2])
m4_define([version_minor], [6])
m4_define([version], [version_major.version_minor])

AC_PREREQ([2.65])
AC_INIT([SpaceShooter], [version], [al3xbio@gmail.com])
AC_CONFIG_SRCDIR([src/main.c])

AM_INIT_AUTOMAKE([SpaceShooter], [version])

# Checks for programs.
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_LN_S

# Define macros.
AU_ALIAS([AC_DEFINE_DIR], [AX_DEFINE_DIR])
AC_DEFUN([AX_DEFINE_DIR], [
  prefix_NONE=
  exec_prefix_NONE=
  test "x$prefix" = xNONE && prefix_NONE=yes && prefix=$ac_default_prefix
  test "x$exec_prefix" = xNONE && exec_prefix_NONE=yes && exec_prefix=$prefix
  eval ax_define_dir="\"[$]$2\""
  eval ax_define_dir="\"$ax_define_dir\""
  AC_SUBST($1, "$ax_define_dir")
  AC_DEFINE_UNQUOTED($1, "$ax_define_dir", [$3])
  test "$prefix_NONE" && prefix=NONE
  test "$exec_prefix_NONE" && exec_prefix=NONE
])

# Custom config header.
AC_CONFIG_HEADERS([src/config.h])
AH_TEMPLATE([DATA_PATH], [Define datafile path.])
AX_DEFINE_DIR([DATA_PATH], [datadir/spaceshooter/SpaceShooter.dat])

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h],, AC_MSG_ERROR(stdlib missing.))
AC_CHECK_HEADERS([allegro.h],, AC_MSG_ERROR(Allegro lib missing.))

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_CHECK_FUNCS([mkdir])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT

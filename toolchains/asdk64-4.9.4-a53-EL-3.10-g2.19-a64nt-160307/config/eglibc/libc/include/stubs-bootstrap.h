/* Placeholder stubs.h file for bootstrapping.

   When bootstrapping a GCC/EGLIBC pair, GCC requires that the EGLIBC
   headers be installed, but we can't fully build EGLIBC without that
   GCC.  So we run the command:

      make install-headers install-bootstrap-headers=yes

   to install the headers GCC needs, but avoid building certain
   difficult headers.  The <gnu/stubs.h> header depends, via the
   EGLIBC subdir 'stubs' make targets, on every .o file in EGLIBC, but
   an empty stubs.h like this will do fine for GCC.  */

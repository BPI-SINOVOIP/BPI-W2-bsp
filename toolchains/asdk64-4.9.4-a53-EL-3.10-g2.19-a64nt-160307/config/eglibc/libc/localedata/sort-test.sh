#! /bin/sh
# Test collation using xfrm-test.
# Copyright (C) 1997-2014 Free Software Foundation, Inc.
# This file is part of the GNU C Library.

# The GNU C Library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.

# The GNU C Library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.

# You should have received a copy of the GNU Lesser General Public
# License along with the GNU C Library; if not, see
# <http://www.gnu.org/licenses/>.

set -e

common_objpfx=$1; shift
test_program_prefix=$1; shift
lang=$*

id=${PPID:-100}
here=`pwd`

# Run collation tests.
status=0
for l in $lang; do
  here=0
  cns=`echo $l | sed 's/\(.*\)[.][^.]*/\1/'`
  LOCPATH=${common_objpfx}localedata GCONV_PATH=${common_objpfx}/iconvdata \
   LC_ALL=$l ${test_program_prefix} \
   ${common_objpfx}localedata/collate-test $id < $cns.in \
   > ${common_objpfx}localedata/$cns.out || here=1
  cmp -s $cns.in ${common_objpfx}localedata/$cns.out || here=1
  if test $here -eq 0; then
    echo "$l collate-test OK"
  else
    echo "$l collate-test FAIL"
    diff -u $cns.in ${common_objpfx}localedata/$cns.out | sed 's/^/  /'
    status=1
  fi

  LOCPATH=${common_objpfx}localedata GCONV_PATH=${common_objpfx}/iconvdata \
   LC_ALL=$l ${test_program_prefix} \
   ${common_objpfx}localedata/xfrm-test $id < $cns.in \
   > ${common_objpfx}localedata/$cns.xout || here=1
  cmp -s $cns.in ${common_objpfx}localedata/$cns.xout || here=1
  if test $here -eq 0; then
    echo "$l xfrm-test OK"
  else
    echo "$l xfrm-test FAIL"
    diff -u $cns.in ${common_objpfx}localedata/$cns.xout | sed 's/^/  /'
    status=1
  fi
done

exit $status
# Local Variables:
#  mode:shell-script
# End:

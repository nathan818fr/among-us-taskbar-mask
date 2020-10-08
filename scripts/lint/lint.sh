#!/bin/bash
cd "$(dirname "$(readlink -f "$0" || realpath "$0")")" || exit

python3 ./.cpplint.py --quiet --root ../../src/ --linelength 120 -- \
  $(find ../../src \( -name "*.cpp" -or -name "*.h" \)) \
  2>&1 | sed 's#../../src/#src/#g'
exit $?

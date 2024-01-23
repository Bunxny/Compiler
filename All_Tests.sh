#!/bin/sh
TESTER=~/cs350/A-folder-of-examples/.bin/All_Tests.sh
if test "${#}" -eq 0
then
  ${TESTER}
else
  ${TESTER} "$@"
fi
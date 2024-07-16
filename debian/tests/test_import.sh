#!/bin/sh
set -eu
cd "$AUTOPKGTEST_TMP"

for python in $(py3versions -s); do
    for module in $@; do
        echo "${python} -c \"import ${module}\""
        ${python} -c "import ${module}"
        echo "${python}-dbg -c \"import ${module}\""
        ${python}-dbg -c "import ${module}"
    done
done

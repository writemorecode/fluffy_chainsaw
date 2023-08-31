#!/bin/bash

set -euo pipefail

if [[ "$#" -ne 1 ]]; then
    echo "Usage: $0 <program.calc>"
    exit 1
fi

BASENAME=$(basename "$1")
PROGRAM_NAME=$(echo "${BASENAME}" | cut -d '.' -f1)

NEW_NAME="${PROGRAM_NAME}.c"
touch "${NEW_NAME}"

cat lexyacc-code/header.c > "${NEW_NAME}"

bin/calc3c.exe < "$1" >> "${NEW_NAME}"

cat lexyacc-code/footer.c >> "${NEW_NAME}"

gcc -L lib/ -O2 "${NEW_NAME}" obj/stack.o -o "${PROGRAM_NAME}" -lfunctions


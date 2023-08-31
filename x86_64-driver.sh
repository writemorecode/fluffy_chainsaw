#!/bin/bash

if [[ "$#" -ne 1 ]]; then
    echo "Usage: $0 <program.calc>"
    exit 1
fi

BASENAME=$(basename "$1")
PROGRAM_NAME=$(echo "${BASENAME}" | cut -d '.' -f1)

NEW_NAME="${PROGRAM_NAME}.s"
touch "${NEW_NAME}"

cat lexyacc-code/header.s > "${NEW_NAME}"

bin/calc3i.exe < "$1" >> "${NEW_NAME}"

cat lexyacc-code/footer.s >> "${NEW_NAME}"

gcc -L lib/ "${NEW_NAME}" -o "${PROGRAM_NAME}" -lfunctions


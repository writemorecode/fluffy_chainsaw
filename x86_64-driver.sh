#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <program.calc>"
    exit 1
fi

BASENAME=$(basename "$1")
PROGRAM_NAME=$(echo "$BASENAME" | cut -d '.' -f1)

NEW_NAME="$PROGRAM_NAME.s"
touch "$NEW_NAME"

cat code/header.s > "$NEW_NAME"

./code/calc3i.exe < "$1" >> "$NEW_NAME"

cat code/footer.s >> "$NEW_NAME"

gcc -L code/extras -ggdb3 "$NEW_NAME" -o "$PROGRAM_NAME" -lfactorial -llntwo -lgcd


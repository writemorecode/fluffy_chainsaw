#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <program.calc>"
    exit 1
fi

BASENAME=$(basename "$1")
PROGRAM_NAME=$(echo "$BASENAME" | cut -d '.' -f1)

NEW_NAME="$PROGRAM_NAME.s"
touch "$NEW_NAME"

echo ".intel_syntax noprefix" > "$NEW_NAME"
echo ".data" >> "$NEW_NAME"
echo 'fmt_str: .asciz "%d\n"' >> "$NEW_NAME"
echo -e "ARRAY:\n.quad 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0\n"  >> "$NEW_NAME"

echo ".text" >> "$NEW_NAME"
echo ".global main" >> "$NEW_NAME" 
echo "main:" >> "$NEW_NAME"

./code/calc3b.exe < "$1" >> "$NEW_NAME"

echo -e "\tmov\trax, 60" >> "$NEW_NAME"
echo -e "\tmov\trdi, 0" >> "$NEW_NAME"
echo -e "\tsyscall" >> "$NEW_NAME"

gcc -L code/extras -ggdb3 "$NEW_NAME" -o "$PROGRAM_NAME" -lfactorial -llntwo -lgcd



#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <program.calc>"
    exit 1
fi

BASENAME=$(basename "$1")
PROGRAM_NAME=$(echo "$BASENAME" | cut -d '.' -f1)

NEW_NAME="$PROGRAM_NAME.c"
touch "$NEW_NAME"

cat code/header.c > "$NEW_NAME"

./code/calc3c.exe < "$1" >> "$NEW_NAME"

cat code/footer.c >> "$NEW_NAME"

gcc -L code/extras -O2 -ggdb3 "$NEW_NAME" -o "$PROGRAM_NAME" -lfactorial -llntwo -lgcd -lprint -lstack


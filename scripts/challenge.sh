#!/bin/sh

for i in $(seq 1 2); do
    file="./assets/maze$i.txt"
    maze="$(cat "$file")"
    rows="$(echo "$maze" | wc -l)"
    collumns="$(tail -1 "$file" | wc -m)"
    collumns="$((collumns - 1))"

    echo "$collumns"
    echo "$rows"
    echo "$maze"

./build/maze --challenge <<EOF
$collumns
$rows
$maze
EOF

done

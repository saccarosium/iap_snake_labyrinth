#!/bin/sh

build() {
./build/maze --challenge <<EOF
$1
$2
$3
EOF
}

if [ -n "$1" ]; then
    file="./assets/maze$1.txt"
    [ -f "$file" ] || exit 1
    maze="$(cat "$file")"
    rows="$(echo "$maze" | wc -l)"
    collumns="$(tail -1 "$file" | wc -m)"
    collumns="$((collumns - 1))"
    echo "$collumns"
    echo "$rows"
    echo "$maze"
    build "$collumns" "$rows" "$maze"
else
    mazes="$(find . ./assets/*.txt | wc -l)"
    for i in $(seq 1 "$mazes"); do
        file="./assets/maze$i.txt"
        [ -f "$file" ] || exit 1
        maze="$(cat "$file")"
        rows="$(echo "$maze" | wc -l)"
        collumns="$(tail -1 "$file" | wc -m)"
        collumns="$((collumns - 1))"
        echo "$collumns"
        echo "$rows"
        echo "$maze"
        build "$collumns" "$rows" "$maze"
    done
fi

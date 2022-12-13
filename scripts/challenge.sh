#!/bin/sh

maze="$(cat ./assets/maze1.txt)"

./build/maze --challenge << EOF
10
6
$maze
EOF

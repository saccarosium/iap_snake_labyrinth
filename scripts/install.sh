#!/bin/sh

installed() {
    if type "$1" >/dev/null 2>&1; then
        return 0
    else
        return 1
    fi
}

if installed apt && [ -x /bin/apt ]; then
    echo "Installing ncurses with apt"
    if [ "$(id -u)" = 0 ]; then
        apt update
        apt install libncurses6
    else
        sudo apt update
        sudo apt install libncurses6
    fi
    exit 0
fi

if installed dnf; then
    echo "Installing ncurses with dnf"
    if [ "$(id -u)" = 0 ]; then
        dnf install ncurses-devel
    else
        sudo dnf install ncurses-devel
    fi
    exit 0
fi

if installed pacman; then
    echo "Installing ncurses with pacman"
    if [ "$(id -u)" = 0 ]; then
        pacman -Sy ncurses
    else
        sudo pacman -Sy ncurses
    fi
    exit 0
fi

if installed apk; then
    echo "Installing ncurses with apk"
    if [ "$(id -u)" = 0 ]; then
        apk add ncurses-libs
    else
        sudo apk add ncurses-libs
    fi
    exit 0
fi

if installed brew; then
    echo "Installing ncurses with brew"
    brew install ncurses
    exit 0
fi

#!/bin/bash
# Lance tous les fichiers de maps/ sous valgrind et affiche un résumé lisible.
# Usage : ./run_tests.sh   (depuis la racine du projet, après make)

BIN=./cub3D
GREEN='\033[32m'; RED='\033[31m'; YELLOW='\033[33m'
CYAN='\033[36m'; GRAY='\033[90m'; BOLD='\033[1m'; RESET='\033[0m'
PASS=0; FAIL=0

# run <code attendu> <fichier>
run() {
	local expected=$1 file=$2 out code msg status
	out=$(valgrind -q --leak-check=full --show-leak-kinds=all \
		--errors-for-leak-kinds=all --error-exitcode=42 "$BIN" "$file" 2>&1)
	code=$?
	msg=$(echo "$out" | grep -v '^==' | sed -n '2p')
	if [ "$code" -eq 42 ]; then
		status="${RED}LEAK${RESET}"; FAIL=$((FAIL + 1))
	elif [ "$code" -eq "$expected" ]; then
		status="${GREEN} OK ${RESET}"; PASS=$((PASS + 1))
	else
		status="${RED}FAIL${RESET}"; FAIL=$((FAIL + 1))
		msg="exit $code au lieu de $expected  $msg"
	fi
	printf "%b  ${CYAN}%-42s${RESET} ${GRAY}%s${RESET}\n" "$status" "$(basename "$file")" "$msg"
	if [ "$code" -eq 42 ]; then
		echo "$out" | grep '^==' | sed 's/^/        /'
	fi
}

section() { printf "\n${BOLD}${YELLOW}── %s ──${RESET}\n" "$1"; }

if [ ! -x "$BIN" ]; then
	echo "Binaire $BIN introuvable : lance make d'abord."
	exit 1
fi

section "valid (exit 0 attendu)"
for f in maps/valid/*.cub; do run 0 "$f"; done

section "invalid/header"
for f in maps/invalid/header/*.cub; do run 1 "$f"; done

section "invalid/map"
for f in maps/invalid/map/*.cub; do run 1 "$f"; done

section "invalid/file"
for f in maps/invalid/file/*; do run 1 "$f"; done
run 1 maps/invalid/file/.cub
run 1 maps/nexiste_pas.cub

printf "\n${BOLD}Résultat : ${GREEN}%d OK${RESET}${BOLD}, ${RED}%d échec(s)${RESET}\n" "$PASS" "$FAIL"
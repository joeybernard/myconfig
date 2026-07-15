#!/usr/bin/env bash
# netsnap — summarize active network connections
set -euo pipefail

BOLD='\033[1m'
RESET='\033[0m'
echo -e "${BOLD}Established connections by remote host:${RESET}"
ss -tnp state established \
    | awk 'NR>1 {print $4}' \
    | sed 's/:[0-9]*$//' \
    | sort | uniq -c | sort -rn \
    | awk '{printf "  %4d  %s\n", $1, $2}' \
    | head -20
echo ""
echo -e "${BOLD}Connection states summary:${RESET}"
ss -tan \
    | awk 'NR>1 {print $1}' \
    | sort | uniq -c | sort -rn \
    | awk '{printf "  %4d  %s\n", $1, $2}'
echo ""
echo -e "${BOLD}Listening services (TCP):${RESET}"
ss -tlnp \
    | awk 'NR>1 {printf "  %-25s %s\n", $4, $NF}'


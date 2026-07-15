#!/usr/bin/env bash
# sysbrief — quick system health snapshot
set -euo pipefail

BOLD='\033[1m'
RESET='\033[0m'
RED='\033[0;31m'
YELLOW='\033[0;33m'
GREEN='\033[0;32m'
section() { echo -e "\n${BOLD}── $1 ──${RESET}"; }
section "System Information"
echo "Host   : $(hostname)"
echo "Kernel : $(uname -r)"
section "Uptime & Load"
uptime -p
awk '{printf "Load avg: %.2f %.2f %.2f\n", $1, $2, $3}' /proc/loadavg
section "Memory"
free -h | awk 'NR==2 {
    used=$3; total=$2; avail=$7
    printf "Used: %s / %s  |  Available: %s\n", used, total, avail
}'
section "Disk Usage (>70%)"
df -h --output=target,pcent,size,avail | awk 'NR==1 || $2+0 > 70 {
    if (NR==1) print; else print "\033[0;33m" $0 "\033[0m"
}'
section "Top 5 CPU Consumers"
ps -eo pid,comm,%cpu,%mem --sort=-%cpu | head -6
section "Swap"
swapon --show 2>/dev/null || echo "No swap configured"


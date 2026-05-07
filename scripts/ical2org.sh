#!/bin/bash

# Grab the DRAC Outlook calendar
python3 ~/repos/Pical2org/pical2org.py -o ~/my_org/drac_outlook.org https://outlook.office365.com/owa/calendar/76529b53d3d64efd956dd377958fc5c8@alliancecan.ca/71a27ea4de514fdeb68426dea03a501411738982182761455362/calendar.ics -f

# Grab the DRAC Google calendar
python3 ~/repos/Pical2org/pical2org.py -o ~/my_org/drac_gcal.org https://calendar.google.com/calendar/ical/joey.bernard%40gw.alliancecan.ca/private-544e253b15a3b76b3dbf9dd75081ae98/basic.ics -f

# Grab my own personal calendar
python3 ~/repos/Pical2org/pical2org.py -o ~/my_org/gcal.org https://calendar.google.com/calendar/ical/druid.bernard%40gmail.com/private-6fe0c18dc92c51f1c6646fc3f7c94203/basic.ics -f

# Grab my UNB calendar
python3 ~/repos/Pical2org/pical2org.py -o ~/my_org/unb.org https://outlook.office365.com/owa/calendar/ef9e8bf4c2f64d4faa08a7d828f99e84@unb.ca/cde34430e78d418b90b14926e4fed07e4299525889863396979/calendar.ics -f


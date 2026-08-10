---
tags:
  - D2L
  - D2L
  - Archives
created: 2024-06-25T09:20
updated: 2025-04-09T21:12
---
When doing a selection of courses for a copyright audit, we can use the following command line

`grep "Course Offering" OrganizationalUnits.csv | grep 2024WI | cut -f1,5 -d',' | grep ED_ | shuf -n 1 >>export.csv`

The department codes to pull are

- ED
- MBA
- ADM
- PHYS
- GGE
- CE
- CHEM
- PSYC
- CS
- ENV
- MAAC
- BIOL
- KIN
- BA
- CHE
- POLS
- ECE
- ME
- SOCI
- ANTH
- ENGL
- INDG
- GE
- ECON
- FILM
- MATH
- CCS
- CRIM
- NURS
- HIST
- ITAL
- ARTS
- CMUS
- STAT
- PHIL
- EDUC
- FR
- ADED
- LAW
- JPNS
- FOR
- EE
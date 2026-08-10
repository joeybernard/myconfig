---
tags:
  - MOTUS
created: 2024-09-24T20:49
updated: 2025-04-09T21:13
---



# Database sizes
MariaDB [(none)]> SELECT table_schema AS "Database",
    -> ROUND(SUM(data_length + index_length) / 1024 / 1024, 2) AS "Size (MB)"
    -> FROM information_schema.TABLES
    -> GROUP BY table_schema;

| Database           | Size (MB) |
|------------------|-----------|
| data_uploads       | 2.63      |
| information_schema | 0.17      |
| motus              | 85172.56  |
| motus_testing      | 1.67      |
| mysql              | 0.62      |
| performance_schema | 0.00      |
| uploads            | 2.25      |

7 rows in set, 3 warnings (0.23 sec)


# MOTUS Table sizes
MariaDB [(none)]> SELECT table_name AS "Table",
    -> ROUND(((data_length + index_length) / 1024 / 1024), 2) AS "Size (MB)"
    -> FROM information_schema.TABLES
    -> WHERE table_schema = "motus"
    -> ORDER BY (data_length + index_length) DESC;

| Table                 | Size (MB) |
|-----------------------|----------|
| hits                  | 77004.92  |
| runs                  | 3179.94   |
| batchRuns             | 2306.94   |
| batches               | 913.97    |
| pulseCounts           | 820.75    |
| uploads               | 469.36    |
| gps                   | 148.72    |
| projBatch             | 136.69    |
| batchParams           | 115.30    |
| tempBatchOverlaps     | 48.58     |
| tagDeps               | 10.06     |
| hits_with_bad_runIDs  | 9.52      |
| batchProgs            | 4.03      |
| tagAmbig              | 2.03      |
| recvDeps              | 1.42      |
| deviceIDsernoMap      | 0.13      |
| hitFixes              | 0.05      |
| reprocessBatches      | 0.03      |
| reprocessBootSessions | 0.02      |
| _ambigTagProj         | 0.02      |
| reprocess             | 0.02      |
| bumpCounter           | 0.02      |
| tempRunUpdates        | 0.02      |
| batchRunFixes         | 0.02      |
| projAmbig             | 0.02      |
| maxKeys               | 0.02      |
| runFixes              | 0.02      |
| _batches              | NULL      |
| _runs                 | NULL      |

29 rows in set (0.00 sec)

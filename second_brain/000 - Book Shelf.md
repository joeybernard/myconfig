---
created: 2026-05-12T21:41
updated: 2026-05-12T22:28
---
To Read
```dataview
TABLE WITHOUT ID
"![cover|80](" + cover + ")" AS "Cover",
title,
author, series
FROM "2_Literature/Books"
WHERE shelf="toread"
SORT title ASC
```

Currently Reading
```dataview
TABLE WITHOUT ID "![cover|80](" + cover + ")" AS "Cover", title, author, series FROM "2_Literature/Books" 
WHERE shelf="reading" SORT started ASC
```

Done Reading
```dataview
TABLE WITHOUT ID "![cover|80](" + cover + ")" AS "Cover", title, author, series FROM "2_Literature/Books" 
WHERE shelf="read" SORT title ASC
```

Stopped Reading
```dataview
TABLE WITHOUT ID "![cover|80](" + cover + ")" AS "Cover", title, author, series FROM "2_Literature/Books" WHERE shelf="stopped" SORT title ASC
```
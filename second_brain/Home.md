---
created: 2023-03-15T22:54
updated: 2026-02-20T09:26
---

## Vault Info
| 🗄️ Recent file updates                                                      | To Read                                                                                              | Favourites                                                                        |
| ---------------------------------------------------------------------------- | ---------------------------------------------------------------------------------------------------- | --------------------------------------------------------------------------------- |
| `$=dv.list(dv.pages('').sort(f=>f.file.mtime.ts,"desc").limit(4).file.link)` | `$=dv.list(dv.pages('"ReadItLater" and -#read').sort(f=>f.file.mtime.ts,"desc").limit(4).file.link)` | `$=dv.list(dv.pages('#favorite').sort(f=>f.file.name,"desc").limit(4).file.link)` |


〽️ Stats
	-  File Count: `$=dv.pages().length`
	-  Project Count: `$=dv.pages('"4_Project"').length`

## Active Items
### Open Projects
`$=await dv.list(dv.pages('"4_Project"').sort(f=>f.file.mtime.ts,"desc").limit(6).file.link)` 

### Open Tasks
```tasks
not done
path does not include Readwise
```

Fleeting Notes
```dataview
TABLE WITHOUT ID 
	file.link as "1_Fleeting Notes", 
	(date(today) - file.cday).day as "Days alive" 
FROM "1_Fleeting"
SORT file.cday asc 
```
---
created: 2026-04-15T16:05
updated: 2026-04-15T16:36
---
## 15-04-2026 - 16:36
- Delete the allocation and RAP
```
alloc1 = Allocation.find_by_alloc_id('esx-055-ab-001')
alloc1.destroy
rap1 = ResourceAllocationProject.find_by_groupname('rrg-dbillett')
rap1.destroy
```

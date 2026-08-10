---
created: 2026-06-30T15:14
updated: 2026-06-30T15:41
---

There is a process that runs every 20 minutes, coming from IP address 199.241.162.32. It hits the endpoint
`/export/changes/1771352349`
where the number is from what date that they are looking for changes from. They pull
- consortium
- institution
- department
- position
- research_area
- specific_research_area
- committee
- resource
- cluster
- roles
- raps
All of these are unscoped, so they will pull any changes to terminated entries. The code is in
```
app/controllers/export_controller.rb
```
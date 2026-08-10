---
created: 2026-01-07T16:13
updated: 2026-01-07T16:32
---
- get the list of tables with
```
ActiveRecord::Base.connection.tables
```
- get columns from a model
```
Person.inspect
OR
Person.attribute_names
Person.attribute_types
```
---
created: 2026-05-01T13:57
updated: 2026-05-01T13:57
---
Sometimes, the test DB misses migrations. If this happens, you can apply them manually with

```
RAILS_ENV=test bundle exec rails db:migrate
```
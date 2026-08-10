---
created: 2026-01-15T12:22
updated: 2026-06-03T11:45
---
- In order to silence deprecation warnings, use the following
```
bundle exec rspec --deprecation-out /dev/null

```
- When correcting an MR, you can do the update on the branch and then push with ```push --force-with-lease```
- To restart your dev application, use ```touch tmp/restart.txt```
- HTTP: [https://ccdb-ng.driirn.ca](https://ccdb-ng.alliancecan.ca/), SSH: `ccdb-ng.alliancecan.ca` (use your ccdb username and the SSH key you’d use to get into the old prod server; once in, you can use `sudo -i -u ccdb` to access the ccdb account that runs the app)
---
The development database is a snapshot from production but the test database is more distinct.  It doesn't automatically pick up the schema but you can (and will sometimes need to) pull the schema from the development database.  This isn't an issue in CI since it builds it all from scratch in containers every run.  
`bundle exec rake db:migrate`  
to make sure your dev db is up to date and then run  
`bundle exec rake db:schema:load`  
to force the test database schema to be updated
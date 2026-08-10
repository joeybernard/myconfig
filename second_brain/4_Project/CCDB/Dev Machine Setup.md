---
created: 2025-12-11T11:08
updated: 2026-07-03T08:53
---

Fraser is responsible for setting up a development machine. It is hosted on the cloud infrastructure. My development machine is named
- bernardj@ccdbdev-ng.driirn.ca
One gotcha could be the DB permissions on the development database. This needs to be configured as its own step.
Once everything is setup and running, should be able to access the front end from
- http://bernardj-ccdbdev-ng.alliancecan.ca/

---
Access is through SSH keys. When you want to access the associated database machine, you need to setup an agent and do key forwarding. You need a configuration file with the following
```
Host vm-ccdbdb
    ForwardAgent yes
```
Then you can get there with the commands
- eval "$(ssh-agent)"
- ssh-add .ssh/id_ed25519
- ssh -A bernardj@ccdbdev-ng.driirn.ca
Then you can use
- ssh postgres@vm-ccdbdb
This will reset your copy of the database. The reset is a reload from the "parent" copy of the dev DB. This parent gets updated every night.


You can check database access by starting with the rails console
- bundle exec rails console
- Person.count
You can migrate DB information and setup the test DB with
```
# you don't need to do this part every time 
bundle exec rake db:migrate 
bundle exec rake db:test:load_schema
```

---
In order to do some testing, you can
- bundle exec rspec
If you want to just run a single group
- bundle exec rspec spec/models
If you want to run a specific test
- bundle exec rspec spec/features/javascript/rpp_application_spec.rb

---
You can select your ruby version by using
- ./script/rails_version.sh

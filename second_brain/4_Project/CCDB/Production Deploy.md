---
created: 2026-02-02T09:57
updated: 2026-02-20T09:31
---
Production deploy: su as `ccdb` and then inside the repo execute `script/production-deploy.sh`  
  
It'll prompt you to either review the changes you're deploying (C), bail (N) or actually do the deploy (Y)  
  
---  
  
I wrote myself a convenience script to do the su and put me in the right dir -- if you want to borrow it:  
```
> cat switch-to-ccdb.sh
#!/bin/sh

set -eu

sudo -u ccdb -s /bin/bash -c "cd /data/ccdb/ccdb-portal && /bin/bash"
```
---
When running scripts in prod, you'll need to pass an env var `RAILS_ENV=production`

---
tags:
  - Computing
  - Linux
source: https://www.reddit.com/r/linux/comments/agixs/is_there_something_that_can_synchronize_installed/
created: 2023-05-03T11:31
updated: 2026-07-27T15:17
---

It is sometimes useful to copy a list of installed packages from one machine to another. Found these instructions:

-----
Given that Ubuntu uses dpkg and apt for package management, it's quite easy. If you just want to sync one way (i.e. make a 2nd computer identical to the first) do this on the 1st:

dpkg --get-selections > packages.txt

Then copy the packages.txt file to the 2nd machine and do:

sudo dpkg --clear-selections  
sudo dpkg --set-selections < packages.txt
sudo apt-get dselect-upgrade

This will

-   set every package to "deinstall"
    
-   set the packages from packages.txt to "install"
    
-   actually perform the package installation/deinstallation and upgrading required.
    

If you want the sync to go both ways, you need a way to merge the package lists generated on each machine. I would recommend using something like git for this, or maybe just diff3 and patch.
---
tags: Computing,Linux
created: 2023-05-15T15:17
updated: 2025-04-09T21:12
---

mdadm is the main utility when dealing with software based RAID on Linux systems. You can always check the current status of a RAID system with
```
cat /proc/mdstat
```

If you want more detail, you can use
```
sudo mdadm --detail /dev/mdX
```
where mdX is the RAID device you are interested in.

On most Linux systems, there will be a cron job that syncs everything up. For example, on Centos, it is located at
```
[jbernard@chain-data2 ~]$ cat /etc/cron.d/raid-check
# Run system wide raid-check once a week on Sunday at 1am by default
0 1 * * Sun root /usr/sbin/raid-check

```
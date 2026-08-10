# 5 Terminal Commands I Run on Every Fresh Linux Install

![rw-book-cover](https://static0.makeuseofimages.com/wordpress/wp-content/uploads/wm/2025/12/several-containers-open-in-distrobox.jpg)

## Metadata
- Author: [[Raghav Sethi]]
- Full Title: 5 Terminal Commands I Run on Every Fresh Linux Install
- Category: #articles
- Summary: The author shares five helpful terminal commands to use after installing Linux, like setting aliases and syncing the clock with Windows. These tips make using Linux easier and faster, especially for new users. Learning the terminal can be hard at first but is very useful over time.
- URL: https://www.makeuseof.com/terminal-commands-i-run-on-every-fresh-linux-install/

## Highlights
- When you dual-boot between the two, each OS "corrects" the clock based on its own assumptions, which causes the time to completely mess up after each boot. This has a really easy fix, though. Just type in this command in the terminal:
  timedatectl set-local-rtc 1 --adjust-system-clock 
  After this, you just need to reboot your machine, and your system clock won't break anymore. ([View Highlight](https://read.readwise.io/read/01kgfj00wr9dbgg5wpxrxafxt1))
- To see all the services that run during boot and how much time they take, run:
  systemd-analyze blame 
  This lists boot processes in descending order based on how long they take to start. Instead of disabling services at random, look for the ones taking an unusually long time. ([View Highlight](https://read.readwise.io/read/01kgfj0kjcz1apxrs67yggf4q9))

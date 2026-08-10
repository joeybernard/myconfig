# If You Dual-Boot Linux, Don't Make These Costly 4 Mistakes

![rw-book-cover](https://static0.makeuseofimages.com/wordpress/wp-content/uploads/wm/2026/02/grub-showing-dualbooted-computer.jpg)

## Metadata
- Author: [[Afam Onyimadu]]
- Full Title: If You Dual-Boot Linux, Don't Make These Costly 4 Mistakes
- Category: #articles
- Summary: Dual-booting Linux and Windows needs care because Windows updates can remove Linux from the boot menu. Always back up the EFI System Partition and check boot order after updates. Also, manage Windows security features and filesystems carefully to avoid data loss or boot problems.
- URL: https://www.makeuseof.com/if-you-dual-boot-linux-dont-make-these-costly-mistakes/

## Highlights
- EFI System Partitions range between 100MB and 512MB and are typically formatted as FAT32 on modern computers. This appears as EFI System Partition on the Windows Disk Management tool, and Linux mounts it at **/boot/efi**. This partition includes the **\EFI\Microsoft\Boot** directory, and after installing Ubuntu, the **\EFI\ubuntu** directory. EFI System Partitions include Windows Boot Manager and GRUB’s EFI binaries; and the firmware first loads from this location before the OS starts. ([View Highlight](https://read.readwise.io/read/01khkmey52hym3fvtztn1wgv1d))
- Attempting to fix a faulty multi-boot environment by reinstalling GRUB with a live USB and **chroot** is incomplete on its own. When your computer goes through a major recovery operation, in addition to overwriting ESP files, Windows also modifies firmware UEFI variables. This action will re-prioritize Windows Boot Manager, making it essential to verify boot order in BIOS/UEFI after a repair, since merely restoring files doesn't restore firmware boot order. ([View Highlight](https://read.readwise.io/read/01khkmg1rserwhzg3q1f3wwn6j))
- My failsafe is backing up the ESP itself, twice: a Windows-only state, then a confirmed working dual-boot state. This is the workflow: back up, modify, back up again. The moment there's a problem, I can use [Clonezilla](https://clonezilla.org/) to restore the ESP image before confirming the boot order in firmware. It's far more reliable and faster to restore a 100 to 512MB partition than to manually construct boot entries. As long as you dual-boot without ESP backups, the next disaster is always an update away. ([View Highlight](https://read.readwise.io/read/01khkmgp3t6eqmrk3h4ge4az41))
- Windows version upgrades create a problem. The process typically resets your device's UEFI boot entries. While the update leaves GRUB untouched, Windows doesn’t prioritize GRUB in firmware NVRAM. This creates the impression that Linux has been erased. ([View Highlight](https://read.readwise.io/read/01khkmkkx762m5qxef5xr0p38e))
- Windows Recovery can be even more destructive because it rebuilds the boot configuration data inside the ESP, and Linux EFI entries are overwritten. A partition containing Linux may be intact, but the firmware may still be unable to point to it. While the data is preserved, the boot path is destroyed. ([View Highlight](https://read.readwise.io/read/01khkmkv4wvqtq52s6x7rg88wh))

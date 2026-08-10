# [How to Shrink a WSL2 Virtual Disk – Stephen Rees-Carter](https://stephenreescarter.net/how-to-shrink-a-wsl2-virtual-disk/)

I’m a huge fan of [Windows Subsystem for Linux](https://docs.microsoft.com/en-us/windows/wsl/about) (WSL), especially [WSL2](https://docs.microsoft.com/en-us/windows/wsl/wsl2-index) which uses a virtualisation layer to bring increased performance and compatibility to WSL. However, one of the few downsides of WSL2 is that it uses a virtual disk (VHDX) to store the filesystem. This means you can end up in a situation where your virtual disk is taking up 100GB, but WSL2 only needs 15GB… which is exactly what happened to me today!

Long story short, I saved a backup in the wrong directory, and my WSL2 disk expanded to use up all available space on my drive. I went looking for a way to shrink a WSL2 virtual disk, and after a few false starts, found a method which worked for me. Hopefully it’ll help you out too!

## Before you begin

Before shrinking a WSL2 virtual disk, you need to ensure that WSL2 is not running.

You can check if it’s running with the command ‘`wsl.exe --list --verbose`‘ in PowerShell:

```
PS C:\Users\valorin> wsl.exe --list --verbose
  NAME            STATE           VERSION
* WLinux          Running         2
  Debian          Stopped         2
  Ubuntu-18.04    Stopped         2
  kali-linux      Stopped         2
```

It should stop when it’s idle, or you can encourage it to stop with the ‘`wsl.exe --terminate`‘ command:

```
PS C:\Users\valorin> wsl.exe --terminate WLinux
```

**I also highly recommend you take a backup of your WSL2 installation.**

These instructions worked for me, but you could have a different environment that may result in corrupted data. So please, take a backup first!

## Use `diskpart` to Shrink a WSL2 Virtual Disk

I discovered you can use the ‘`diskpart`‘ tool to compact a VHDX. This allows you to shrink a WSL2 virtual disk file, reclaiming disk space. It appeared to work for me without any data corruption, taking the file size down from 100GB to 15GB. Your results may vary though.

You can launch the `diskpart` tool in PowerShell:

```
PS C:\Users\valorin> diskpart
```

It will open up a new window:

Once that has opened, you need to specify the path to your VHDX file.

If you don’t know this path, you can find by first locating the package directory for your WSL2 instance, which lives in: `C:\Users\valorin\AppData\Local\Packages\`. Look for the vendor name, such as `WhitewaterFoundryLtd.Co` for **Pengwin**, `CanonicalGroupLimited` for **Ubuntu**, or `TheDebianProject` for **Debian**. Once you’ve identified the folder, you’ll find the VHDX in the `LocalState` subdirectory.

For me, this path is:  
`C:\Users\valorin\AppData\Local\Packages\WhitewaterFoundryLtd.Co.16571368D6CFF_kd...\LocalState\ext4.vhdx`

With the full path to the VHDX, you can select it within `diskpart`:

```
DISKPART> select vdisk file="C:\Users\valorin\AppData\Local\Packages\WhitewaterFoundryLtd.Co.16571368D6CFF_kd...\LocalState\ext4.vhdx"

DiskPart successfully selected the virtual disk file.
```

Once it’s selected, you can ask `diskpart` to compact it:

```
DISKPART> compact vdisk

  100 percent completed

DiskPart successfully compacted the virtual disk file.	
```

Once that has finished, you can close `diskpart`.

If you check your VHDX now, you should see it has reduced in size. It depends how much empty space was being used by WSL2 as to how big a space reduction there will be. In my case, it was quite significant:

**Before**

```
Mode                 LastWriteTime         Length Name
----                 -------------         ------ ----
d-----         9/02/2020  12:04 PM                temp
-a----         9/02/2020   1:04 PM    94778687488 ext4.vhdx
-a----        29/07/2019   3:48 PM              0 fsserver
```

**After**

```
Mode                 LastWriteTime         Length Name
----                 -------------         ------ ----
d-----         9/02/2020  12:04 PM                temp
-a----         9/02/2020   1:04 PM    14533263360 ext4.vhdx
-a----        29/07/2019   3:48 PM              0 fsserver
```

I hope you found this useful. ?

Please let me know if you have an alternate way to shrink a WSL2 virtual disk – especially if it’s safer than this approach.
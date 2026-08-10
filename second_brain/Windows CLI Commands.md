---
tags:
  - Windows
  - Computing
created: 2024-06-27T13:35
updated: 2025-04-09T21:12
---
## Basic Commands

| Command Name | **Command Purpose**                                      |
| ------------ | -------------------------------------------------------- |
| ver          | Display the Windows version                              |
| help         | Provide a list of available commands and their uses      |
| cls          | Clear the screen                                         |
| dir          | List files and directories in the current directory.     |
| cd           | Change the current directory.                            |
| mkdir        | Create a new directory.                                  |
| rmdir        | Remove a directory                                       |
| copy         | Copy one or more files to another location.              |
| move         | Move or rename files and directories.                    |
| del          | Delete one or more files.                                |
| ren          | Rename a file or directory.                              |
| type         | Display the contents of a text file.                     |
| echo         | Display a message or turn command echoing on or off.     |
| exit         | Close the Command Prompt window.                         |
| ping         | Test network connectivity to a specified host.           |
| ipconfig     | Display network configuration information.               |
| netstat      | Display network statistics and connections.              |
| tasklist     | List currently running processes.                        |
| taskkill     | Terminate a running process.                             |
| shutdown     | Shut down or restart the computer.                       |
| systeminfo   | Display detailed system information.                     |
| sfc /scannow | Run System File Checker to scan and repair system files. |
| chkdsk       | Check a disk and display a status report.                |
| diskpart     | Open the disk partitioning tool.                         |
| sc           | Communicate with the Service Control Manager.            |

## Directory Navigation

| Command Name          | Command Purpose                                                              | Example Command                      |
| --------------------- | ---------------------------------------------------------------------------- | ------------------------------------ |
| cd                    | Change the current directory.                                                | cd C:\Users\YourName\Documents       |
| cd ..                 | Move up one directory level.                                                 | cd ..                                |
| cd                    | Move to the root directory of the current drive.                             | cd                                   |
| dir                   | List files and directories in the current directory.                         | dir                                  |
| dir /p                | List directory contents one page at a time.                                  | dir /p                               |
| dir /s                | List directory contents including all subdirectories.                        | dir /s                               |
| dir C:                | List files and directories in the specified directory.                       | dir C:\Windows                       |
| mkdir                 | Create a new directory.                                                      | mkdir NewFolder                      |
| md                    | Create a new directory (same as **mkdir**).                                  | md NewFolder                         |
| rmdir                 | Remove an empty directory.                                                   | rmdir OldFolder                      |
| rmdir /s              | Remove a directory and all its contents.                                     | rmdir /s OldFolder                   |
| attrib                | Display or change file attributes.                                           | attrib +r C:\Users\YourName\file.txt |
| tree                  | Display directory structure in a tree format.                                | tree                                 |
| tree C:\Program Files | Display tree structure for a specific directory.                             | tree C:\Program Files                |
| pushd                 | Save and change the current directory.                                       | pushd D:\Projects                    |
| popd                  | Restore the previous directory saved by the **pushd** command.               | popd                                 |
| chdir                 | Change the current directory (same as **cd**).                               | C:\Users\YourName                    |
| chdir /d              | Change the drive and the directory.                                          | chdir /d D:\Games                    |
| path                  | Display or set a search path for executable files.                           | path                                 |
| path C:\Program Files | Set the search path for executable files.                                    | path C:\Program Files                |
| subst                 | Map a path to a drive letter.                                                | subst X: C:\Users\YourName\Downloads |
| vol                   | Display the volume label and serial number of a drive.                       | vol C:                               |
| diskpart              | Open the disk partitioning tool.                                             | diskpart                             |
| mountvol              | Create, delete, or list a volume mount point.                                | mountvol X: /d                       |
| fsutil                | Perform tasks related to file systems or disk volumes.                       | fsutil fsinfo drives                 |
| sort                  | Takes input from a file or directory and sources its content alphabetically. | sort file.txt                        |
| move                  | Move or rename files and directories.                                        | move C:\temp\file.txt D:\Documents   |
| copy                  | Copy one or more files to another location.                                  | copy file.txt D:\Backup              |

## Disk Management

| **Command Name** | **Command Purpose**                                           | **Example Command**                    |
| ---------------- | ------------------------------------------------------------- | -------------------------------------- |
| chkdsk           | Check a local disk and repair problems                        | chkdsk C:                              |
| chkdsk /f        | Check and fix errors on the disk.                             | chkdsk /f C:                           |
| cipher           | Encrypt or decrypt files and directories.                     | cipher /e C:\SensitiveData             |
| cipher /w        | Permanently overwrite deleted data on a volume.               | cipher /w:C:                           |
| defrag           | Defragment and optimize a specified drive.                    | defrag C:                              |
| defrag /C        | Defragment all local volumes.                                 | defrag /C                              |
| chkntfs          | Display or modify the checking of disk drives at startup.     | chkntfs C:                             |
| chkntfs /d       | Restore the default behavior of checking drives at startup.   | chkntfs /d                             |
| diskpart         | Open the disk partitioning tool.                              | diskpart                               |
| format           | Format a disk for use with Windows.                           | format D:                              |
| label            | Create, change, or delete the volume label of a disk.         | label C: MyVolume                      |
| mountvol         | Create, delete, or list a volume mount point.                 | mountvol X: /d                         |
| diskpart         | Run the disk partitioning tool for advanced disk management.  | diskpart                               |
| sfc              | Scan and repair system files.                                 | sfc /scannow                           |
| fsutil           | Perform tasks related to file systems or disk volumes.        | fsutil fsinfo drives                   |
| wmic             | Retrieve detailed information about disks and partitions.     | wmic diskdrive list brief              |
| cleanmgr         | Open the Disk Cleanup utility.                                | cleanmgr                               |
| compact          | Display or alter the compression of files on NTFS partitions. | compact /c /s:C:\MyFolder              |
| diskmgmt.msc     | Open the Disk Management GUI tool.                            | diskmgmt.msc                           |
| convert          | Convert a volume from FAT32 to NTFS.                          | convert C: /FS:NTFS                    |
| mount            | Mount a file system.                                          | mountvol                               |
| robocopy         | Robust file copy for mirroring directories.                   | robocopy C:\Source D:\Destination /MIR |
| xcopy            | Copy files and directories, including subdirectories.         | xcopy C:\Source D:\Destination /E      |

## Networking

| **Command Name** | **Command Purpose**                                                     | **Example Command**              |
| ---------------- | ----------------------------------------------------------------------- | -------------------------------- |
| arp              | Displays and modifies the ARP cache.                                    | arp -a                           |
| assoc            | Displays or modifies file extension associations.                       | assoc .txt=txtfile               |
| ftp              | Transfers files to and from a remote network location.                  | ftp example.com                  |
| getmac           | Displays the MAC address of network adapters.                           | getmac                           |
| hostname         | Displays the name of the current host.                                  | hostname                         |
| ipconfig         | Displays IP configuration information.                                  | ipconfig /all                    |
| netsh            | Configures network settings and displays statistics.                    | netsh interface show interface   |
| netstat          | Displays active network connections and statistics.                     | netstat -an                      |
| nslookup         | Queries the DNS to obtain domain name or IP address mapping.            | nslookup example.com             |
| ping             | Tests connectivity between the local machine and a remote network host. | ping google.com                  |
| route            | Displays and modifies the IP routing table.                             | route print                      |
| tracert          | Traces the path from the local computer to a remote network host.       | tracert google.com               |
| telnet           | Communicates with a remote device using the Telnet protocol.            | telnet example.com 23            |
| tftp             | Transfers files to and from a remote TFTP server.                       | tftp -i 192.168.1.1 put file.txt |
| net              | A collection of commands for network operations.                        | net view \\server                |
| netsh wlan       | Manages wireless network settings.                                      | netsh wlan show profiles         |
| pathping         | Combines ping and tracert functions to identify network latency issues. | pathping google.com              |
| nbtstat          | Displays NetBIOS over TCP/IP statistics.                                | nbtstat -a <device name>         |
| net user         | Manages user accounts on the network.                                   | net user username /add           |
| net localgroup   | Manages local user groups on the network.                               | net localgroup administrators    |
| net use          | Connects, disconnects, and displays network drives.                     | net use Z: \\server\share        |
| net session      | Lists or disconnects sessions with the local computer.                  | net session                      |
| net share        | Creates, deletes, or displays shared resources.                         | net share sharename=c:\path      |
| net start        | Stops a network service.                                                | net start service                |
| net stop         | Stops a network service.                                                | net stop service                 |
| net statistics   | Displays statistics about the workstation or server.                    | net statistics workstation       |
| net time         | Displays or synchronizes the local machine's time with another server.  | net time \\server                |
| net print        | Displays print queue status and controls print jobs.                    | net print \\server\printer       |

## Miscellaneous

| **Command Name** | **Command Purpose**                                                        | **Example Command**                                                  |
| ---------------- | -------------------------------------------------------------------------- | -------------------------------------------------------------------- |
| auditpol         | Displays or sets audit policies.                                           | auditpol /get /category:*                                            |
| bcdboot          | Creates or repairs system partition boot files.                            | bcdboot C:\Windows /s C:                                             |
| bcedit           | Manages Boot Configuration Data (BCD).                                     | bcedit /set {default} bootstatuspolicy ignoreallfailures             |
| bdehdcfg         | Manages BitLocker encrypted drives.                                        | bdehdcfg -driveinfo                                                  |
| bitsadmin        | Manages Background Intelligent Transfer Service jobs.                      | bitsadmin /list /allusers                                            |
| bootcfg          | Configures, queries, or changes Boot.ini file settings.                    | bootcfg /query                                                       |
| bootsect         | Updates the master boot code for hard disk partitions.                     | bootsect /nt60 C:                                                    |
| certreq          | Performs certification authority (CA) certificate requests.                | certreq -new request.inf request.cer                                 |
| certutil         | Manages Certification Authority (CA) files and services.                   | certutil -backupDB "C:\Backup"                                       |
| chglogon         | Enables, disables, or queries logons at the terminal server.               | chglogon /enable                                                     |
| chgport          | Lists or changes COM port mappings for DOS compatibility.                  | chgport COM1=COM2                                                    |
| chgusr           | Changes .ini file mapping for the current user.                            | chgusr /execute                                                      |
| clip             | Redirects output to the Windows clipboard.                                 | clip < readme.txt                                                    |
| cmdkey           | Creates, lists, and deletes stored user names and passwords.               | cmdkey /list                                                         |
| doskey           | Edits command lines, recalls Windows commands, and creates macros.         | doskey /history                                                      |
| driverquery      | Lists installed device drivers and their properties.                       | driverquery /v                                                       |
| date             | Displays or sets the date for the system                                   | date 05-18-2024                                                      |
| diskraid         | Manages software RAID configurations.                                      | diskraid /status                                                     |
| dispdiag         | Generates a diagnostic log of the display adapter.                         | dispdiag                                                             |
| djoin            | Provisions a computer account in the domain.                               | djoin /provision /domain domain.com /machine machine1                |
| logman           | Manages and schedules performance counter and event trace log collections. | logman query                                                         |
| mode             | Configures system devices.                                                 | mode con cols=80 lines=50                                            |
| nbstat           | Displays NetBIOS over TCP/IP statistics.                                   | nbtstat -a <device name>                                             |
| openfiles        | Displays files opened by remote users.                                     | openfiles /query                                                     |
| powercfg         | Configures power settings and displays power configurations.               | powercfg /hibernate on                                               |
| reg              | Manages the Windows registry.                                              | reg query HKLM\Software\Microsoft                                    |
| sc               | Communicates with the Service Controller and installed services.           | sc query                                                             |
| schtasks         | Schedules commands and programs to run at a specific time.                 | schtasks /create /tn "My Task" /tr "C:\task.bat" /sc daily /st 09:00 |
| setx             | Sets environment variables permanently.                                    | setx PATH "%PATH%;C:\NewPath"                                        |
| timeout          | Delays execution for a specified time.                                     | timeout /t 10                                                        |
| title            | Sets the Command Prompt window title.                                      | title New Title                                                      |
| tzutil           | Displays the timezone of your system                                       | tzutil /g                                                            |
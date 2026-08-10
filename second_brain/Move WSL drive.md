---
tags: Computing, WSL, Windows
created: 2023-03-20T10:33
updated: 2025-04-09T21:12
---

When you want to move the WSL virtual drive, follow these instructions:
- wsl --shutdown
- mkdir D:\\WSL
- mkdir D:\\backup
- cd D:\\backup
- wsl --export Ubuntu ubuntu.tar
- wsl --unregister Ubuntu
- wsl --import Ubuntu "D:\\WSL\\ubuntu" "D:\\backup\\ubuntu.tar"
- cd $env:USERPROFILE\\AppData\\Local\\Microsoft\\WindowsApps
- ubuntu config --default-user jbernard
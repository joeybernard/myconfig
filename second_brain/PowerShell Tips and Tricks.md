---
tags:
  - Computing
created: 2023-12-13T09:55
updated: 2025-04-09T21:12
---

- You can have proper bash-like tab completion by adding
	- Set-PSReadlineKeyHandler -Key Tab -Function MenuComplete
	You need to add this to your profile.ps1 file, located in
	- %UserProfile%\\Documents\\PowerShell\\profile.ps1
	- %UserProfile%\\Documents\\WindowsPowerShell\\profile.ps1


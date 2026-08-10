---
tags:
  - D2L
  - D2L
  - Archives
created: 2024-04-19T09:35
updated: 2025-04-09T21:12
---
When writing any HTML in D2L widgets, you have a series of replace strings available, based on the current course and logged in user. These are

```
<p>OrgID: {OrgId}</p>
<p>OrgName: {OrgName}</p>
<p>OrgUnitId: {OrgUnitId}</p>
<p>OrgUnitName: {OrgUnitName}</p>
<p>OrgUnitCode: {OrgUnitCode}</p>
<p>OrgUnitTypeId: {OrgUnitTypeId}</p>
<p>OrgUnitPath: {OrgUnitPath}</p>
<p>UserId: {UserId}</p>
<p>UserName: {UserName}</p>
<p>OrgDefinedId: {OrgDefinedId}</p>
<p>FirstName: {FirstName}</p>
<p>LastName: {LastName}</p>
<p>Email: {Email}</p>
<p>ExternalEmail: {ExternalEmail}</p>
<p>InternalEmail: {InternalEmail}</p>
<p>RoleId: {RoleId}</p>
<p>RoleCode: {RoleCode}</p>
<p>RoleName: {RoleName}</p>
<p>HelpDeskEmail: {HelpDeskEmail}</p>
<p>HelpDeskName:{HelpDeskName}</p>
<p>LoginPath: {LoginPath}</p>
<p>PasswordResetLink: {PasswordResetLink}</p>
```

If you want to use curly braces in your HTML, you can escape them with a second curly brace.
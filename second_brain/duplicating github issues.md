---
tags: Computing
created: 2023-05-16T10:05
updated: 2025-07-16T12:59
---

In order to create duplicates of github issues, you need to create a custom Actions workflow and add a file named ```duplicate_issue.yml```. This file has the following contents:

```
name: Duplicate Issue
on:
  issue_comment:
    types: [created]
jobs:
  run:
    runs-on: ubuntu-latest
    steps:
      - uses: wow-actions/duplicate-issue@v1
        with:
          GITHUB_TOKEN: ${{ secrets.GITHUB_TOKEN }}
```

This is triggered when you use the comment
```
/duplicate
```

Then github actions bot will make a copy at the next run.
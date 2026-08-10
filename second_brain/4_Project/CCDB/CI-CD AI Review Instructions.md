---
created: 2026-06-25T14:41
updated: 2026-06-26T10:30
---
## How has this been tested and how can others test it?[](#how-has-this-been-tested-and-how-can-others-test-it)

1. Open an MR pipeline and confirm the `copilot` job runs by default.
2. Push with `-o ci.variable="SKIP_COPILOT_REVIEW=true"` or use a commit message containing `[skip-copilot-review]`, then confirm the `copilot` job is skipped.
3. Push with `-o ci.variable="COPILOT_REVIEW_ONLY=true"` or use a commit message containing `[copilot-review-only]`, then confirm `lint`, `rails72ruby32alma`, and `jira-sync` are skipped while the `copilot` job remains eligible on MR pipelines.

## How would you use this?[](#how-would-you-use-this)

1. Run normal CI plus Copilot review:

**Push normally, with no special variable and no marker in the latest commit message.**

`git push origin your-branch`

2. Skip only the Copilot review job:

**Either push with a variable:**

`git push -o ci.variable="SKIP_COPILOT_REVIEW=true" origin your-branch`

**Or put this in the latest commit message:**

`[skip-copilot-review]`

3. Run review-only behavior:

**This skips the regular MR-pipeline jobs that were wired for this feature, while leaving the copilot job eligible.**

**Variable form:**

`git push -o ci.variable="COPILOT_REVIEW_ONLY=true" origin your-branch`

Commit-message form: `[copilot-review-only]`

**Important behavior:**

- The copilot job is MR-only, so review-only mode is only useful once the branch has a merge request.
- For MR pipelines, the most reliable control is the latest commit message marker.
- GitLab checks the latest commit that triggered the pipeline. If your newest commit does not include [copilot-review-only], full CI will run again.
- If you want to go back to full CI, push a new top commit without either marker.

A simple workflow is:

```
git commit -m "Update CI controls [copilot-review-only]"
git push origin your-branch
```

And when you want full CI again:

```
git commit --allow-empty -m "Run full CI"
git push origin your-branch
```

Or amend the previous commit and remove [copilot-review-only].


# You can control the AI thinking level
1. Push a branch with `git push -o ci.variable="COPILOT_REVIEW_THINKING_LEVEL=high"`.
2. Confirm the `copilot` MR pipeline job posts a review note that includes `Thinking level: high`.
3. Push with an invalid value for `COPILOT_REVIEW_THINKING_LEVEL` and confirm the job exits with the allowed-values error.
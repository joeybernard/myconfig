---
created: 2025-12-31T13:56
updated: 2025-12-31T14:03
---
Section 4.4

# Analysis of Variance (ANOVA)

## One-way ANOVA
- The null hypothesis is that all population means are equal.
- So, the alternative hypothesis is that at least one is different.
- requirements
	- the samples are random and selected from approximately normal distributions
	- the samples are independent of one another
	- the population variances are approximately equal
- can use the F-distribution if these requirements are met
- the test statistic is the ratio of the variance between samples divided by the variance within samples
Python
- f_oneway()
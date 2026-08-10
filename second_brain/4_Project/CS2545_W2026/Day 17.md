---
created: 2025-12-30T18:37
updated: 2025-12-30T19:19
---
Section 4.1

# Statistical Inference and Confidence Intervals

- point estimate - a single value that is used to estimate a population value - a sample mean is a point estimate
- confidence interval - the range that a population parameter sits within
- margin of error - an indication of the maximum error in an estimate
- confidence level - the probability that the interval estimate will contain the population parameter

sample (or sampling) distribution
- the mean of the sample means is equal to the population mean
- the standard deviation of the sample means is equal to the population standard deviation divided by the square root of the sample size

central limit theorem
- if random samples are taken from any population with mean u and standard deviation, where the sample size is at least 30, then the distribution of the sample means approximates a normal distribution
- if random samples are taken from a population that is normally distributed with mean u and standard deviation, then the sample means approximates a normal distribution for any sample size

confidence interval for the mean when the population standard deviation is known
- a random sample is selected from the population
- the sample size is at least 30, or the underlying population is known to follow a normal distribution
- the population standard deviation is known
- the margin of error formula - page 151

confidence interval for the mean when the population standard deviation is unknown
- a random sample is selected from the population
- the sample size is at least 30, or the underlying population is known to follow a normal distribution
- the population standard deviation is unknown, the sample standard deviation can be calculated
- the margin of error formula - page 154
- t-distributions

confidence interval for proportions
- a random sample is selected from the population
- verify that the normal approximation to the binomial distribution is appropriate by ensuring that both np-hat and n(1-p-hat) are both at least 5, where p-hat represents the sample proportion
	- p - population proportion, typically unknown
	- p-hat - sample proportion (x/n)
	- x - number of successes in the sample
	- n - sample size
- margin of error formula - page 157


sample size determination
- can rearrange margin of error formulas to get the needed sample size for a given margin of error


bootstrapping methods
- when the conditions above are not met, can "fake" it by repeatedly taking sub-samples, with replacement
- a nonparametric method, since we don't assume anything about the underlying probability distribution


Python scipy.stats
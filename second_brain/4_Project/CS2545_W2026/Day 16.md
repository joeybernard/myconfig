---
created: 2025-12-30T16:27
updated: 2025-12-30T16:48
---
Section 3.5

# Discrete and Continuous Probability Distributions

- random variable - a variable where a single value is assigned to a specific outcome
- discrete random variable - there is a finite or countable number of values possible
- continuous random variable - variable can take on any value within a given range

- discrete probability distributions
	- binomial distribution - there are two possible outcomes
		- probability mass function (PMF) - probability of getting exactly x successes in n trials, each with probability p - page 132
	- Poisson distribution - applied when counting the number of occurrences in a certain interval; the random variable then counts the number of occurrences in the interval
		- probability of x successes - page 134
- continuous probability distributions
	- PDF (probability density function) - calculates the area beneath the probability density curve, giving the total probability of that the random variable will fall in the given range; total area always equals 1
	- normal, or bell, distribution
		- standard normal distribution - mean = 0, standard deviation = 1
		- any normal distribution can be standardized by converting to z-scores
		- empirical rule - ~68% within 1 std, ~95% within 2 std, ~99.7% within 3 std

Python - scipy.stats
- distributions
	- binom()
	- poisson()
	- expon()
	- norm()

E.G. - binomial distribution
```python
from scipy.stats import binom

n = 10 # number of trials in the experiment
p = .5 # probability of success
x = 4 # number of successes in the experiment

binom.pmf(x, n, p)  # probability mass function
```
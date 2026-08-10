---
created: 2026-03-12T19:11
updated: 2026-03-12T19:18
---
30 is considered a minimum sample size primarily because of the [Central Limit Theorem (CLT)](https://www.investopedia.com/terms/c/central_limit_theorem.asp), which states that as sample size approaches 30, the distribution of the sample mean becomes approximately normal, allowing the use of z-tests and normal approximation methods. It acts as a pragmatic, historical rule of thumb (often attributed to [William Gosset](https://www.youtube.com/watch?v=ixfy7BzNIHc)) balancing data reliability with cost-effectiveness, representing a threshold where the sample is large enough to reasonably approximate a normal distribution, even if the underlying population is not.

**Key Reasons for the Rule of Thumb:**

- **Central Limit Theorem (CLT):** The sampling distribution of the mean tends toward normality as n increases; n=30is generally viewed as a "good enough" threshold for this approximation.
- **Balancing Act:** It is a compromise between needing enough data to reduce sampling error (and improve precision) and the practical limitations of cost and time.
- **Threshold for "Large" Sample:** It distinguishes between small samples (where t-distributions are necessary) and large samples (where z-tests can be used).
- **Diminishing Returns:** Beyond roughly 30 samples, the additional knowledge gained about the population starts to decrease, making it a point of diminishing returns.
**Important Considerations:**

- **Not a Hard Rule:** The number 30 is not a strict rule; for highly skewed distributions, a much larger sample size may be required.
- **Context Matters:** In some cases, such as in [genome-wide association studies](https://pmc.ncbi.nlm.nih.gov/articles/PMC11379640/), n=30 is far too small.
- **Alternative Approaches:** Modern statisticians often prefer power analysis to determine the precise minimum sample size needed to detect a specific effect, rather than relying on the arbitrary 30
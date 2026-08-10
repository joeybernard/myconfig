---
created: 2025-12-30T16:00
updated: 2025-12-30T16:06
---
Section 3.3

# Measures of Position
- percentiles - percent below a certain given value
- quartiles - divided into 4
	- first find the median, the second quartile
	- first quartile is the median of the lower half
	- third quartile is the median of the top half
- IQR - interquartile range
	- the difference between the third quartile and the first quartile
	- gives  a measure of the variability of the center 50% of the data, removing outliers
- z-score - a measure of how many standard deviations away from the mean a given value is
	- can use z-scores to decide if a value is an outlier, maybe 3 standard deviations away

Python DataFrame.describe() gives quartiles.
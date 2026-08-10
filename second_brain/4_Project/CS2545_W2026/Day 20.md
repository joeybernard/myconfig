---
created: 2025-12-30T21:45
updated: 2025-12-31T13:54
---
Section 4.3

# Correlation and Linear Regression Analysis
- independent variable - the variable that you change or control
- dependent variable - the variable that you measure
- scatter plots visualize the data
- correlation coefficient (Pearson correlation coefficient) - r - formula on page 191
- Python - pearsonr()
- interpretation of r
	- strength of correlation based on the value of r
	- direction of correlation based on sign of r
	- r always between -1 and 1
	- r=0 means there is NO linear relationship
	- r=1 means perfect positive correlation
	- r=-1 means perfect negative correlation

---

## Linear regression
Once you have shown a correlation, a regression model can be developed.
- least squares - minimize the squared distances from the data points to the fitted line
- residual - the difference between an observed y-value and the predicted y-value
- assumptions
	- There is a linear relationship in the population that models the average value of y for varying values of x. In other words, the expected value of y for each particular value lies on a straight line in the population.
	- The y-values for any particular x-value are normally distributed about the line.
	- The standard deviations of the population y-values about the line are equal for each value of x.
	- The residual errors are mutually independent.
	- The data are produced from a well-designed random sample or randomized experiment.

Python
- pearsonr()
- linregress()
- plt.scatter()
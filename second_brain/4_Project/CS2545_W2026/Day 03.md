---
created: 2025-12-24T15:23
updated: 2026-01-05T13:45
---
Section 1.5
Python Data Science
- use pandas to manage datasets
```python
import pandas as pd

data = pd.read_csv("path/to/file.csv")
data
```
- this gives you a DataFrame object
- you get basic descriptive statistics
```python
data.describe()
```
- you can get a single column
```python
data["col_name"]
```
- iloc gives much more control
```python
data.iloc[:,2]  # select all values in the second column
data.iloc[3,:] # select all values in the third row
data.iloc[[1,3],[2,3]] # select the rows at index 1 and 3, the columns at index 2 and 3
```
- search with loc
```python
data.loc[data["col_name"] == 'Search Text']

data.loc[(data['col1'] == 'text1') & (data['col2'] > val2)]
```

Visualization
```python
import matplotlib.pyplot as plt
plt.scatter(data['col1'],data['col2'])
```

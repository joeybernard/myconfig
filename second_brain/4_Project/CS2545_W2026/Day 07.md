---
created: 2025-12-24T16:37
updated: 2026-01-05T13:46
---
Section 2.3

- web scraping - getting data from web sites
- APIs (Application Programming Interface) are awesome
- web scraping
	- web crawling
	- XPath
	- regex
	- HTML parsing
	- APIs
		- XML 
		- JSON

## Web crawling
```python
import pandas as pd

df_list = pd.read_html("https://fred.stlouisfed.org/release/tables?rid=50&eid=3149#snid=4498")
df = df_list[0]
print(df.head(5))
```

## Regex
```python
import re
initial_text = "This is a text about Python programming"

pattern = "Python"

words = re.findall(pattern, story)
print(words)
```

## CSV files
```python
import csv

....
```

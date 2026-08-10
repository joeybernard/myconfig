## Python Pub 2
---
## Reading Excel Files

---
- Reading data is so common that it is one of the first things you learn
- Most workshops only look at CSV files for ease of use
- A lot people already have data in Excel spreadsheets

---
- There are lots of modules available
- Unless you have a niche need, you should probably stick with pandas
- You will likely be using pandas for other tasks anyway

---
- The most basic way to use it is
```python
import pandas as pd
df = pd.read_excel("my_file.xslx")

display(df)
```
- pandas pulls in data, but not formulas

---
- By default, you only get the first sheet
```python
df = pd.read_excel("my_file.xls", sheet_name = "Sheet2")
```
or
```python
df = pd.read_excel("my_file.xls", sheet_name = 2)
```
- This is either a 0-index value, or the string name for the appropriate sheet in the file

---
- You can grab more than one sheet at a time
```python
dfs = pd.read_excel("my_file.xls", sheet_name = [0, 2, "Sheet5"])
```
or
```python
dfs = pd.read_excel("my_file.xls", sheet_name = None)  # All sheets
```
- These are returned as a dictionary of dataframes



---
## Searching PDFs for Keywords

---
- As always, there are loads of modules available
- We will use pypdf
- There is a pypdf2, but it has been discontinued and future work is going into pypdf

---
- First need to do the imports
```python
from pypdf import PdfReader 
from pathlib import Path
```

---
- Then setup some working space
```python
# set directory path 
directoryPath = r"" 
# declare lists and variables 
readers = [] 
filenames = [] 
check = 0
```

---
- Next read in the files
```python
# read PDFs 
for file in Path(directoryPath).glob("*.pdf"): 
    readers.append(PdfReader(str(file))) 
    filenames.append(file.name)
```

---
- Search the files
```python
# search for text in PDFs 
for x in range(0, len(readers)): 
    for i in range(0, len(readers[x].pages)): 
        if "" in readers[x].pages[i].extract_text().lower(): 
            print(f"File: {filenames[x]}, Page: {i+1}") 
            check += 1
```

---
- print out surrounding context
```python
for x in range(0, len(readers)): 
    for i in range(0, len(readers[x].pages)): 
        lines = split(readers[x].pages[i].extract_text(), '.')
        for j in range(0, len(lines)):
            if "" in lines[j].lower(): 
                print(f"File: {filenames[x]}, Page: {i+1}") 
                if j != 0 :
                   print(lines[j-1])
                print(lines[j]
                if j < (len(lines) - 1) :
                    print(lines[j+1])
                check += 1

```
---
- You can do loads of other things with PDFs
- You can edit, add pages, add watermarks
- Merge PDFs
- Read and write annotations

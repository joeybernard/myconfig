---
tags:
---
## Python Pub 1
---
## Virtual Environments

---
- There are several options available for managing virtual environments
- The default standard one is venv
- It should already be available with Python
- There are modules available to work with venv that you might want to explore

---
- Creating a new virtual environment can be done with
```python
python -m venv /path/to/directory
```
- The last parameter is the path to the directory name that you want to use for this virtual environment
- You probably want to use it in the current directory

---
- You have the option of having symlinks to Python and libraries or having them copied into your virtual environment
- The default is different in different environments
- My personal preference is to copy, so that there is no chance of changes
```python
python -m venv --copies ./my_venv
```

---
- Once you are ready to use the virtual environment, you can activate it with
- Windows
```
.\my_venv\Scripts\activate.bat
```
- PowerShell
```
.\my_venv\Scripts\activate.ps1
```
---
- Bash
```
. ./my_venv/Scripts/activate
```

---
- With the environment active, Python uses your folder to hold and search for modules
- pip installs new modules here in this location
- You can install all required modules in one step with
```
pip install -r requirements.txt
```

---
- Once you are all done, you can deactivate your virtual environment
- Windows
```
deactivate.bat
```
- PowerShell
```
deactivate
```
- Bash
```
deactivate
```

---
- Note you don't need to add the path to the deactivate script, since activation added it to your path



---
## Plotting on a globe

---
- matplotlib has a lot of functionality available
- There are also lots of extra modules that build on the core of matplotlib
- We will use basemap to manage the globe part of the plot

---
- Installation
```
pip install matplotlib
pip install basemap
```

---
- Initial imports
```python
from mpl_toolkits.basemap import Basemap
import matplotlib.pyplot as plt
import numpy as np
```

---
- Initialize map
```python
# set up orthographic map projection with
# perspective of satellite looking down at 45N, 100W.
# use low resolution coastlines.
map = Basemap(projection='ortho',lat_0=45,lon_0=-100,resolution='l')
```

---
- Add map components
```python
# draw coastlines, country boundaries, fill continents.
map.drawcoastlines(linewidth=0.25)
map.drawcountries(linewidth=0.25)
map.fillcontinents(color='coral',lake_color='aqua')
```

---
- Add map details
```python
# draw the edge of the map projection region (the projection limb)
map.drawmapboundary(fill_color='aqua')
# draw lat/lon grid lines every 30 degrees.
map.drawmeridians(np.arange(0,360,30))
map.drawparallels(np.arange(-90,90,30))
```

---
- Get data ready (in this case, it is made up data)
```python
# make up some data on a regular lat/lon grid.
nlats = 73; nlons = 145; delta = 2.*np.pi/(nlons-1)
lats = (0.5*np.pi-delta*np.indices((nlats,nlons))[0,:,:])
lons = (delta*np.indices((nlats,nlons))[1,:,:])
wave = 0.75*(np.sin(2.*lats)**8*np.cos(4.*lons))
mean = 0.5*np.cos(2.*lats)*((np.sin(2.*lats))**2 + 2.)
```

---
- Plot and show
```python
# compute native map projection coordinates of lat/lon grid.
x, y = map(lons*180./np.pi, lats*180./np.pi)
# contour data over the map.
cs = map.contour(x,y,wave+mean,15,linewidths=1.5)
plt.title('contour lines over filled continent background')
plt.show()
```

---
![](contour1.png)
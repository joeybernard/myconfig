import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib import cm
from matplotlib.ticker import LinearLocator, FormatStrFormatter
import datetime as dt
import matplotlib.dates as mdates

x,y,z = np.genfromtxt("data.dat", unpack=True)
new_x = [dt.datetime.strptime(str(int(d)), '%Y%m%d%H%M%S') for d in x]
num_x = [(d - min(new_x)).seconds for d in new_x]

fig = plt.figure()
ax = fig.add_subplot(1,1,1,projection='3d')
surf = ax.scatter(num_x, y, z)
#fig.colorbar(surf, shrink=0.5, aspect=5)

plt.show()

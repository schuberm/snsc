import numpy
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
data=numpy.loadtxt("output.txt");

fig = plt.figure()
ax = Axes3D(fig)
ax.plot(data[:,1], data[:,2], data[:,3], zdir='z')
#mt=numpy.loadtxt("mtpair.txt");
#n, bins, patches = plt.hist(lcd[:,0], 200, normed=1, histtype='stepfilled')
#n, bins, patches = plt.hist(mt[:,0], 200, normed=1, histtype='stepfilled')
plt.show()

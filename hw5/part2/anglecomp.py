import numpy
import matplotlib.pyplot as plt
lcd=numpy.loadtxt("lcgangle.txt");
mt=numpy.loadtxt("mtangle.txt");
n, bins, patches = plt.hist(lcd[:], 200, normed=1, histtype='stepfilled')
n, bins, patches = plt.hist(mt[:], 200, normed=1, histtype='stepfilled')
plt.show()

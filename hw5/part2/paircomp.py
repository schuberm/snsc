import numpy
import matplotlib.pyplot as plt
lcd=numpy.loadtxt("lcgpair.txt");
mt=numpy.loadtxt("mtpair.txt");
n, bins, patches = plt.hist(lcd[:,0], 200, normed=1, histtype='stepfilled')
n, bins, patches = plt.hist(mt[:,0], 200, normed=1, histtype='stepfilled')
plt.show()

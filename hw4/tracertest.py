import numpy
import matplotlib.pyplot as plt
data=numpy.loadtxt("output-tracer.txt");
plt.plot(data[:,0], data[:,1])
plt.show()

import numpy
import matplotlib.pyplot as plt
data=numpy.loadtxt("output.txt")
x=numpy.arange(data.shape[1])
for n in range(0,data.shape[0]):
	plt.plot(x,data[n,:])
plt.show()

import numpy
import matplotlib.pyplot as plt

times=numpy.loadtxt("part1timings.txt")
x=numpy.arange(times.shape[1])

for n in range(0,times.shape[0]):
	plt.plot(x,times[n,:], label=str(n))

plt.legend(loc='center left',bbox_to_anchor=(1,0.5),prop={'size':6})
plt.xlabel("Number of Threads")
plt.ylabel("Time [real seconds]")
plt.show()

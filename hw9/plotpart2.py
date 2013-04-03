import numpy
import matplotlib.pyplot as plt

times=numpy.loadtxt("part2timings.txt")

#for n in range(1,3):
plt.plot(times[0,:],times[1,:], label='Blurradius=41')
plt.plot(times[0,:],times[2,:], label='Blurradius=3')

plt.yscale('log')
plt.legend(loc='upper right')
plt.xlabel("Number of Threads")
plt.ylabel("Time [real seconds]")
plt.show()

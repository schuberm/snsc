import numpy
import matplotlib.pyplot as plt
eigvec=numpy.loadtxt("eigvec.txt")
x=numpy.arange(eigvec.shape[1])
eigval=numpy.loadtxt("eigval.txt")

plt.plot(x,eigvec[:,numpy.argmax(eigval)])
plt.plot(x,eigvec[:,numpy.argmin(eigval)])
plt.show()

print min(eigval)
print max(eigval)

D = 1
dt = 0.001
dx=1/100

print D*dt/(dx^2)*max(eigval)


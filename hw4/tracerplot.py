import time
import numpy
import matplotlib.pyplot as plt
rho=numpy.load("rhofield.npy");
particle=numpy.loadtxt("particle.txt");
nframes=rho.shape[0];
plt.ion()
for n in xrange(nframes):
    plt.clf()
    plt.imshow(rho[n,:,:], extent=[-5,5,-5,5])
    plt.plot(particle[n,1],particle[n,2],'ko',markersize=12)
    plt.show()
    plt.draw()

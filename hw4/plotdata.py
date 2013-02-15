import numpy
import matplotlib.pyplot as plt
data=numpy.load("rhofield.npy");
theo=numpy.load("theory.npy");
nframes=data.shape[0];
plt.ion()
for n in xrange(nframes):
    plt.clf()
    plt.imshow(data[n,:,:])
    plt.contour(theo[n,:,:])
    plt.draw()


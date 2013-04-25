import os
import numpy
import subprocess
np=8
nthread=[1,2,4,8]
index=0
output=numpy.zeros(4)
for n in nthread:
	j=16/n
	cmd = "OMP_NUM_THREADS="+str(n)+" mpirun -np " +str(j)+" ./diffusionc-hybrid > OUTPUT_FILE" 
	print cmd
	os.system( cmd)
	for line in open("OUTPUT_FILE"):
		output[index]= output[index]+float(line)
	output[index]=output[index]/j
	print output[index]
	index=index+1

numpy.savetxt("timings2nodes.txt", output)

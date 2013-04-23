import os
import numpy
import subprocess
np=8
nthread=8
output=numpy.zeros((np,nthread))
for j in range(1,np+1):
	for n in range(1,nthread+1):
		cmd = "OMP_NUM_THREADS="+str(n)+" mpirun -np " +str(j)+" ./diffusionc-hybrid > OUTPUT_FILE" 
		print cmd
		os.system( cmd)
		for line in open("OUTPUT_FILE"):
	#		if "real" in line:
	#		output[j-1][n-1]= float(line.split(" ")[-1])
			output[j-1][n-1]= output[j-1][n-1]+float(line)
		output[j-1][n-1]=output[j-1][n-1]/j
		print output[j-1][n-1]

numpy.savetxt("timings64.txt", output)

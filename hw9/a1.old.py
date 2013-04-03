import os
import numpy
br=41
nthread=16
output=numpy.zeros((br,nthread))
for j in range(1,2):
	for n in range(1,2):
		cmd = "{ time -p ./blurppm 001.ppm new001.ppm "+str(j)+" "+str(n)+"; } 2> OUTPUT_FILE"
		print cmd
		os.system( cmd)
		for line in open("OUTPUT_FILE"):
			if "real" in line:
				output[j][n]=float(line.split(" ")[-1])
		print output[j][n]

numpy.savetxt("times.txt", output)

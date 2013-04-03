import os
import numpy
br=41
nthread=16
output=numpy.zeros((br,nthread))
for j in range(1,br+1):
	for n in range(1,nthread+1):
		cmd = "{ time -p ./blurppm 001.ppm new001.ppm "+str(j)+" "+str(n)+"; } 2> OUTPUT_FILE"
		print cmd
		os.system( cmd)
		for line in open("OUTPUT_FILE"):
			if "real" in line:
				output[j-1][n-1]=float(line.split(" ")[-1])
		print output[j-1][n-1]

numpy.savetxt("part1timings.txt", output)

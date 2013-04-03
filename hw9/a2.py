#PROCEDURE
#Get debug node
#qsub -l nodes=1:ppn=8,walltime=2:00:00 -I -X -qdebug
#mkdir/cd to working directory
#vim a2.py, change nthread to number of threads used
#time -p python a2.py | parallel -j 8
#
import os
import subprocess
import numpy

br=3
nthread=16
njob=16
nimages=266
output=numpy.zeros((br,nthread))
joblist='joblist.txt'
jobfile = open(joblist,'w')
os.system("module load gcc gnu-parallel/20120622")

for j in range(0,nimages):
		if j < 10:
			cmd = "{ time -p ./blurppm 00"+str(j)+".ppm new"+str(j)+".ppm "+str(br)+" "+str(nthread)+"; } 2> OUT_"+str(j)+"\n"
		elif 9<j  and j < 100:
			cmd = "{ time -p ./blurppm 0"+str(j)+".ppm new"+str(j)+".ppm "+str(br)+" "+str(nthread)+"; } 2> OUT_"+str(j)+"\n"
		else:
			cmd = "{ time -p ./blurppm "+str(j)+".ppm new"+str(j)+".ppm "+str(br)+" "+str(nthread)+"; } 2> OUT_"+str(j)+"\n"
		print cmd
		jobfile.write(cmd)
jobfile.close()

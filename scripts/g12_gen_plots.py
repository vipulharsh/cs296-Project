import csv

csvFile = open("./data/data.csv", "r")
rerun=[]
Iteration=[]
Stepvalue=[]
alpha=0.00000
loopTime=[]
beta=0.00
count=0
count2=0
for line  in csvFile:
	word=line.split(',')
	#print(word[3])
	if count2 < 100:
		alpha=alpha+float(word[2])
		beta=beta+float(word[6])
		count2=count2+1
	if count2==100:
		Stepvalue.append(alpha/100)
		loopTime.append(beta/100)
		count=count+1
		Iteration.append(count)
		alpha=0.0
		beta=0.0
		count2=0
import matplotlib.pyplot as plt
plt.plot(Iteration,loopTime,'r.',label="Iteration values vs Avg loopTime Time")
plt.plot(Iteration,Stepvalue,'g.',label="Iteration values vs Avg StepTime Time")
plt.axis([0,100,0,40])
plt.xlabel('Iteration Values')
plt.ylabel('Avg StepTime ,Avg loopTime')
plt.title('Iteration Values vs Avg StepTime , Avg loopTime')
plt.legend()
plt.savefig("./plots/g12_plot01.png")
plt.clf()
csvFile.close()
##########################################################################################
csvFile = open("./data/data.csv", "r")
rerun=[]
Iteration=[]
Stepvalue=[]
alpha=0.00000
Velocity=[]
Collision=[]
Position=[]
gamma=0.00
lamda=0.00
beta=0.00
count=0
count2=0
for line  in csvFile:
	word=line.split(',')
	if count2 < 100:
		alpha=alpha+float(word[2])
		beta=beta+float(word[3])
		gamma=gamma+float(word[4])
		lamda=lamda+float(word[5])
		count2=count2+1
	if count2==100:
		Stepvalue.append(alpha/100)
		Collision.append(beta/100)
		Velocity.append(gamma/100)
		Position.append(lamda/100)
		count=count+1
		Iteration.append(count)
		alpha=0.0
		beta=0.0
		count2=0
		lamda=0.00
		gamma=0.00
import matplotlib.pyplot as plt3
plt3.plot(Iteration,Collision,'r.',label="Avg Collision Time")
plt3.plot(Iteration,Stepvalue,'y.' , label="Avg StepTime Time")
plt3.plot(Iteration,Velocity,'b.' ,label="Avg Velocity Time")
plt3.plot(Iteration,Position,'g.' ,label="Avg Position Update Time")
plt3.xlabel('Iteration Values')
plt3.ylabel('Avg StepTime,Collision,Velocity Update,Position Update Times')
plt3.title('Iteration Values vs Different Stats')
plt3.axis([0,100,0,10])
plt3.legend()
plt3.savefig("./plots/g12_plot02.png")
plt3.clf()
csvFile.close()
###########################################################################################
csvFile = open("./data/data.csv", "r")
rerun=[]
IterationR=[]
StepvalueR=[]
alpha=0.00000
loopTimeR=[]
beta=0.00
count=0
count2=0
for x in range(1 ,101):
	StepvalueR.append(0.0)
	loopTimeR.append(0.0)
	rerun.append(x)
for line  in csvFile:
	word=line.split(',')
	val=int(word[0])-1
	StepvalueR[val]=StepvalueR[val]+float(word[2])
	loopTimeR[val]=loopTimeR[val]+float(word[6])
for x in range (1,101):
	StepvalueR[x-1]=StepvalueR[x-1]/100
	loopTimeR[x-1]=loopTimeR[x-1]/100
import matplotlib.pyplot as plt2
plt2.plot(rerun,loopTimeR,'ro',label="rerun values vs Avg loopTime over iteration")
plt2.plot(rerun,StepvalueR,'go',label="rerun values vs Avg StepTime over iteration")
plt2.xlabel('rerun Values')
plt2.ylabel('Avg StepTime ,Avg loopTime over Iteration')
plt2.title('rerun Values vs Avg StepTime,loopTime over iteration')
plt2.axis([0,100,0,40])
plt2.legend()
plt2.savefig("./plots/g12_plot03.png")
plt2.clf()
csvFile.close()
#################################################################################################

csvFile = open("./data/data.csv", "r")
rerun=[]
Iteration=[]
Stepvalue=[]
Collision=[]
Velocity=[]
Position=[]

for x in range(1 ,101):
	Stepvalue.append(0.0)
	Velocity.append(0.0)
	Position.append(0.0)
	Collision.append(0.0)
	rerun.append(x)
for line  in csvFile:
	word=line.split(',')
	val=int(word[0])-1
	Stepvalue[val]=Stepvalue[val]+float(word[2])
	Collision[val]=Collision[val]+float(word[3])
	Velocity[val]=Velocity[val]+float(word[4])
	Position[val]=Position[val]+float(word[5])
for x in range (1,101):
	Stepvalue[x-1]=Stepvalue[x-1]/100
	Collision[x-1]=Collision[x-1]/100
	Velocity[x-1]=Velocity[x-1]/100
	Position[x-1]=Position[x-1]/100
import matplotlib.pyplot as plt4
plt4.plot(rerun,Collision,'ro',label="Avg Collision Time")
plt4.plot(rerun,Stepvalue,'go',label="Avg StepTime")
plt4.plot(rerun,Velocity,'bo',label="Avg Velocity update Time")
plt4.plot(rerun,Position,'yo',label="Avg Position update Time") 
plt4.xlabel('rerun Values')
plt4.ylabel('Avg StepTime,Collision,Velocity Update,Position Update Times')
plt4.title('rerun Values vs Different Stats')
plt4.axis([0,100,0,10])
plt4.legend()
plt4.savefig("./plots/g12_plot04.png")
plt4.clf()
csvFile.close()
#####################################################################################

import math
csvFile = open("./data/data.csv", "r")
rerun=[]
Iteration=[]
Stepvalue=[]
Deviation=[]
alpha=0.00000
loopTime=[]
beta=0.00
count=0
count2=0
stepd=0.0
for line  in csvFile:
	word=line.split(',')
	#print(word[3])
	if count2 < 100:
		alpha=alpha+float(word[2])
		count2=count2+1
	if count2==100:
		Stepvalue.append(alpha/100)
		Iteration.append(count)
		count=count+1
		alpha=0.0
		count2=0
count3=0
count4=0
csvFile.close()
csvFile = open("./data/data.csv", "r")
for line in csvFile:
	word=line.split(',')
	if count3<100:
		stepd=stepd+(float(word[2])-Stepvalue[count4])**2
		count3=count3+1
	if count3==100:
		Deviation.append(math.sqrt(stepd/99))
		stepd=0.0
		count4=count4+1
		count3=0

import matplotlib.pyplot as plt5
plt5.figure()
plt5.errorbar(Iteration,Stepvalue,yerr=Deviation,fmt='r*')
plt5.title("Simplest errorbars, 0.2 in x, 0.4 in y")
plt5.axis([0,100,0,3])
plt5.xlabel("Iteration values")
plt5.ylabel("Error bars Step Time")
plt5.title("Step Time Errorbars Vs Iteration Values")
plt5.savefig("./plots/g12_plot05.png")
plt5.clf()
csvFile.close()
##########################################################################################

import numpy as np
csvFile = open("./data/data.csv", "r")
Interval=[]
Stepvalue=[]
alpha=0.00000
Cummulative=[]
beta=0.00
count=0
count2=0
for line  in csvFile:
	word=line.split(',')
	#print(word[3])
	if word[1] == '15':
		Stepvalue.append(float(word[2]))
		beta=beta+float(word[2])
		Cummulative.append(beta)

counts, bin_edges = np.histogram(Stepvalue, bins=60)
cdf = np.cumsum(counts)
import matplotlib.pyplot as plt6
plt6.plot(bin_edges[1:], cdf,'g-',label="Cumulative frequency")
plt6.hist(Stepvalue,bins=60)
plt6.axis([0,1.5,0,100])
plt6.title("Frequency plot")
plt6.xlabel("StepTime range")
plt6.ylabel("Numbers")
plt6.legend()
plt6.savefig("./plots/g12_plot06.png")
plt6.clf()
csvFile.close()
################################################################################################3


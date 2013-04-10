import sys, string, os , re


csvfile=open("./data/data.csv","w")
for x in range(1,101):
	
	for y in range(1,101):
		path='./bin/cs296_base' +' '+ str(x)
		path=path+' > output'	
		os.system(path)
		filetext=open("output","r")
		string=''
		string=string+str(y)+','
		for line in filetext:
			#print(line)		
			number=re.findall("\d+.\d+",line)
			if len(number) == 0:
				number=re.findall("\d+",line)
			string=string+number[0]+','
		#print(string[:-1])	
		os.remove('output')
		csvfile.write(string[:-1]+'\n')

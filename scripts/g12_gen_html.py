import re

latex = open("./doc/report.tex", "r")
title=''
Plot1=''
text="begin"
for line in latex:
	word=line.split('{')
	text+=line
	if "\\title" in word:
			word2=word[1].split('}')
			title=word2[0]
	if "\\section" in word:
			word2=word[1].split('}')
			Plot1="<h1>" + word2[0] + "</h1>"

htmlTitle="<title>" + title + "</title>"


sections = text.split('\section')
l=len(sections)


"""
print(text)

print("----------------------------------")

for section in sections:
	print ("haha*******************************************************")
	print (section)
#line.replace(char,'')
"""

Contain=[]
headings=[]
Subsections=[]
document="<html" + htmlTitle 

for i in range(1,12):
	
	#print (sections[i])
	heading=sections[i].split('\n', 1)[0]
	
	Contain.append(sections[i].split('\n', 1)[1])
	#print(heading)
	heading=(heading.replace('{','')).replace('}','')
	#print(heading)
	#print(sections[i].split('\n', 1)[1])
	html="<h2>" + heading + "</h2>"
	headings.append(html)
	#print(html)

Sub_sect=[]

for x in range(1,12):
	sec_dict={}
	Sub_sect.append(sec_dict)

for i in range (1 ,12):
	subsection=Contain[i-1].split('\subsection')
	#subsection.replace('\\',"")	
	for sub in subsection:
		if sub != '':
			subhead= sub.split('\n', 1)[0]
			#print(sub)
			subhead=(subhead.replace('{','')).replace('}','')
			Sub_sect[i-1].update({subhead:sub.split('\n', 1)[1].replace('\\',"")})
	
	#print(subsection)



prog = re.compile('includegraphics*')


newline=''


document+="<body>"


for x in range(1,12):
	htmlMain = headings[x-1]
	for word in Sub_sect[x-1]:
		#print(word)	
		#print(Sub_sect[x-1][word])
		tword=""
		content=Sub_sect[x-1][word].split('\n')
		images=""
		#htmlBlock=""		
		for line in content:
			#print(line)
			if prog.match(line):
				line1=line.replace('{','}')
				image = line1.split('}')[1]
				#print(image)
				image=image.replace(".eps",".png")
				image=image.replace("doc/","png/")
				images+='<img src= "' + image +  '"' + 'height="30%"  width="30%"' + '">' + '\n'
			else:
				tword+=line
		htmlMain+='<h3>' + word + '</h3>' + '\n' + '<p>' + tword + '<br>' + images + '</p>' + '\n'
		#print(htmlBlock)
		#print(htmlMain)		
	document+= htmlMain




document+="</body> </html>"			
document=document.replace("textit","")
document=document.replace("enumerate}","")
document=document.replace("begin{","")
document=document.replace("end{","")
document=document.replace("document}","")




file = open("./doc/report.html", "w")
file.write(document)






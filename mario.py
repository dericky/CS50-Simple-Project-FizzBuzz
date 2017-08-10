height = -1
while (height < 0 or height > 23):
    height = int(input("Height: "))

line = '#'
blankspace = height - 1
k = blankspace - height
blanks = " "

for i in  range(0, height):
    blanks = ""
    for j in range(blankspace, 0, -1):
        blanks+=" "
    blankspace = blankspace - 1
    line += "#"
    print(blanks + line)
    
    
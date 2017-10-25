f = open('data.in','r')
fr = open('std.out','w')
def getLong():
    line = f.readline()
    line = line.strip('\n')
    print line
    return long(line)
line = f.readline()
line = line.strip('\n')
line = int(line)
for i in range(line):
    a = getLong();
    b = getLong();
    c = a*b;
    fr.write(str(c))
    fr.write('\n')
f.close()
fr.close()
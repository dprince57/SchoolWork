import re
import sys

def grep(text,regex, before_lines=0, after_lines=0):

    if type(regex) is str:
        regex = re.compile(regex)
    if type(regex) is not re.Pattern:
        raise Exception("grep() function must take a compiled regex or regex string as second argument")
    
    results=[]

    lines=text.split("\n")

    for i in range(len(lines)):
        line = lines[i]
        m=regex.search(line)
        if m:
            start=i-before_lines
            end=i+1+after_lines
            results.append("\n".join(lines[start:end]))

    return results


txt=sys.stdin.read()

li=grep(txt, r'^[A-Z].*[a-z]$')

print("\n".join(li))

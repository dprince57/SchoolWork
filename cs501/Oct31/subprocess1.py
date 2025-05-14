import re
import subprocess


#command="echo Hello $USER ~"
#regex=r'[A-Z]'
try:
    res = subprocess.run("echo Hello $USER ~", shell = True,  capture_output=True, text=True,)

    
    print(res.stdout)

except subprocess.CalledProcessError as e:
    print("An error occurred while running the command:")
    print(e.stderr, end= "")
#if we want to get something in stderr and stdout, we need to add capture_output

#print(res.returncode)

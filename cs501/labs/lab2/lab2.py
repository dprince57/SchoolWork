import re
import subprocess

command = ["cat", "/etc/passwd"]  # Option 1: List contents of /etc/passwd

student_account_pattern = r"[a-zA-Z]{1,4}\d{3}\d{2}"

try:
    result = subprocess.run(command, capture_output=True, text=True, check=True)
    output = result.stdout

    pattern = re.compile(student_account_pattern)

    student_accounts = set(pattern.findall(output))  # Use set to avoid duplicates

    for account in sorted(student_accounts):
        print(account)

except subprocess.CalledProcessError as e:
    print("Error: The command failed to execute.")
except re.error as e:
    print("Error: Invalid regex pattern.")

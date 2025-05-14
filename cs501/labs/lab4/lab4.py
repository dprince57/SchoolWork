words = ['apple', 'banana', 'cherry', 'date', 'avocado', 'blueberry', 'carrot']
result = {letter: [a for a in words if a[0] == letter] for letter in {a[0] for a in words}}
print(result)

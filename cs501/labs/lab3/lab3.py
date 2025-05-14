class PrimeGenerator:
    def __init__(self):
        self.current = 2  # Start from the first prime number

    def is_prime(self, number):
        if number < 2:
            return False
        for i in range(2, int(number ** 0.5) + 1):
            if number % i == 0:
                return False
        return True

    def generate_primes(self, count):
        primes_yielded = 0
        while primes_yielded < count:
            if self.is_prime(self.current):
                yield self.current
                primes_yielded += 1
            self.current += 1

# Usage
prime_gen = PrimeGenerator()
prime_iterator = prime_gen.generate_primes(100)

# Print the first 100 prime numbers
for prime in prime_iterator:
    print(prime)

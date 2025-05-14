##################################################
# _    _  ____  __    ___  _____  __  __  ____   #
#( \/\/ )( ___)(  )  / __)(  _  )(  \/  )( ___)  #
# )    (  )__)  )(__( (__  )(_)(  )    (  )__)   #
#(__/\__)(____)(____)\___)(_____)(_/\/\_)(____)  #
#       ____  _____    ____  _   _  ____         #
#      (_  _)(  _  )  (_  _)( )_( )( ___)        #
#        )(   )(_)(     )(   ) _ (  )__)         #
#       (__) (_____)   (__) (_) (_)(____)        #
#    ____  ____    __    ____  __  __  ____      #
#   (  _ \( ___)  /__\  (  _ \(  \/  )( ___)     #
#    )   / )__)  /(__)\  )(_) ))    (  )__)      # 
#   (_)\_)(____)(__)(__)(____/(_/\/\_)(____)     #
##################################################

Contents:
1. Info
2. Usage
3. Running Time
4. Change Log 

##################################################
##################################################

1. Info

	This program was made by Dakota Prince for
	Dr. Kinne's CS458 Algoritims class. 
	The Assignment was to make a Primality 
	testing machine for primes up to 64 bits
	using Fermat and Miller-Rabin methods.
	This readme contains info for usage and 
	version information.

##################################################
##################################################

2. Usage

	Using this program is simple. First type 
	prime in to the shell. Prime is the main
	program for testing. Next the program 
	should prompt the user on what should 
	he/she should do next. After picking 
	how many times it shall run through, it 
	will test your number. It may take some 
	time to get your number based on what 
	method you choose. 
	(Miller-Rabin not added yet)

##################################################
##################################################

3. Running Time

	using the Fermat Primeality Test you can 
	expect it to take, 
	O(k * log^2n * log log n * log log log n).

	Using Miller-Rabin you can expect a running
	 time of O(k log^3n).

	NOTE: Miller-Rabin will be added in update 0.2.

##################################################
##################################################

4. Change Log

	Version 0.1:
		- Added Fermat test
		- Funcionality up to 64 bit primes

##################################################
##################################################
note to jeff: I added the functionality inside of
the program instead of making it to where they enter
prime test num num. I feel it is a lot less clunky 
and easier on me once I add Miller-Rabin. Also I 
want to make it easier for the user to stay in the 
program and test many numbers
	-Dakota	      

limit coredumpsize 0

setenv LESS 'mqePm Less ?f[%f] .?e-EOF- :?f%pb\% :L\:%lb '
setenv LESSOPEN '|lesspipe.sh %s'
setenv PAGER	"less -s"
setenv READER	"less -s"
setenv EDITOR	jove
setenv FCEDIT	jove
setenv HOSTALIASES	~/.hosts

set nobeep
set prompt = "%n@%m:%/%# "
set mail = /usr/spool/mail/$user
set term = vt100
set autologout = 0

alias dir	'ls -la'
alias rename	mv
alias move	mv
alias delete	rm
alias del	rm
alias deltree	'rm -r'
alias copy	cp
alias type	cat

alias pwd	'echo $cwd'
alias cls	'clear'
alias f		'finger'
alias da	'ls -la'
alias df	'df -h'
alias ..	'cd ..'
alias reset	'echo "\033c"'
alias more	less
alias hide	'chmod og-rwx'

bindkey "	" complete-word-fwd
bindkey	""	history-search-backward

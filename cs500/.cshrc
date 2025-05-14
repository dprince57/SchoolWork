limit coredumpsize 0

setenv LESS 'mqePm Less ?f[%f] .?e-EOF- :?f%pb\% :L\:%lb '
setenv LESSOPEN '|lesspipe.sh %s'
setenv PAGER	"less -s"
setenv READER	"less -s"
setenv EDITOR	jove
setenv FCEDIT	jove
setenv HOSTALIASES	~/.hosts

setenv LC_ALL "en_US.UTF-8"

set nobeep
set prompt = "%n@%m:%/%# "
set mail = /var/mail/$user
set term = xterm
set autologout = 0

alias f		'finger'
alias da	'ls -la'
alias df	'df -h'
alias ..	'cd ..'
alias reset	'echo "\033c"'
alias more	less
alias hide	'chmod og-rwx'
alias pico	'nano -ic --tabsize=2 --tabstospaces --smooth'
alias nano	'nano -wacuWEMOS$ --tabsize=4'
alias nanoi	'nano -ic --tabsize=4 --tabstospaces --smooth'
alias kate	'kate >& /dev/null'

alias mv	'mv -i'
alias rm	'rm -i'
alias cp	'cp -i'

bindkey "	" complete-word-fwd
bindkey	""	history-search-backward

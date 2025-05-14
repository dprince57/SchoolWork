PATH=$PATH:$HOME/bin

alias f="finger"
alias m="mail"
alias vi="vim"

function cssh() {
  if [[ -z $1 ]]; then
    echo "usage: cssh username";
  else
    ssh "$1@cs.indstate.edu";
  fi
}

function resource() {
  source $HOME/.bashrc ;
  echo -e "Finished resourcing";
}

function cppc() {
  if [[ -z $1 ]]; then
    echo "usage: cppc filename";
  else
    g++ -o "$1" "$1.cpp";
  fi
}

function cscp() {
  if [[ -z $2 ]]; then
    echo "usage: cscp username filename/directory";
  else
    scp -r "$1@cs.indstate.edu:$2" .;
  fi
}

function cs() {
  ssh $USER@cs.indstate.edu
}

function csf() {
  if [[ -z $1 ]]; then
    echo "usage: csf <account #>"
  else
    f cs$1
  fi
}

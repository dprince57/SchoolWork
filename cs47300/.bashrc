PATH=$PATH:$HOME/bin

alias f="finger"
alias m="mail"
alias vi="vim"

function cssh() {
  ssh "$1@cs.indstate.edu";
}

function resource() {
  source $HOME/.bashrc ;
  echo -e "Finished resourcing";
}

function cppc() {
  g++ -o "$1" "$1.cpp";
}

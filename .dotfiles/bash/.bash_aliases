# the usual stuff
alias alert='notify-send --urgency=low -i "$([ $? = 0 ] && echo terminal || echo error)" "$(history|tail -n1|sed -e '\''s/^\s*[0-9]\+\s*//;s/[;&|]\s*alert$//'\'')"'
alias egrep='egrep --color=auto'
alias fgrep='fgrep --color=auto'
alias grep='grep --color=auto'
alias l='ls -CF'
alias la='ls -A'
alias ll='ls -alF'
alias ls='ls --color=auto'

# keyball stuff
alias make_keyball='make SKIP_GIT=yes keyball/keyball39:shiotani'
alias flash_keyball='qmk flash -kb keyball/keyball39 -km shiotani'
alias make_and_flash_keyball='make_keyball && flash_keyball'

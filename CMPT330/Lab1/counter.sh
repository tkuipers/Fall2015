#!/bin/bash

blue=`tput setaf 4`
majenta=`tput setaf 5`
reset=`tput sgr0`
if [[ $# = 0 ]]; then
	echo "USAGE $0 item [items ...]"
	exit 1
fi
for arg in $*; do
	# section="$(apropos $arg | grep "^$arg " | grep -Po '\(\d+\w*\)' | sed 's/[(|)]//g' | tr '\n' ' ')"
	section="$(apropos $arg | grep "^$arg " | grep -Po '\(\d+\w*\)' | sed 's/[^0-9|]*//g' | tr '\n' ' ')"
	# echo $section
	echo "${arg} ${section}"
	# echo "$(wc $session)"
	# for s in $section; do
		# man -t -s$s $arg | ps2pdf - > "${arg}(${s}).pdf"
		# echo "${blue}Created: ${majenta}${arg}(${s}).pdf${reset}"
	# done
done

exit 0;
#!/bin/bash

if [[ $# -ne 1 ]]; then
    echo "Wrong number of arguments" >&2
    exit 1
fi

rules_file="$1"
#echo "$rules_file"
if [[ ! -e $PWD/$rules_file ]]; then
	echo "rules file not found!" >&2
	exit 1
fi

temp=$(cat)
#echo "$temp"
packets=$(echo "$temp" | sed -e 's/#.*$//' -e '/^ *$/d')
#echo -e "\n\n~~~~~PACKETS~~~~~~~\n\n\n$packets"

rules=$(sed -e 's/#.*//' -e '/^ *$/d' "$rules_file")
#echo -e "\n\n~~~~~PACKETS~~~~~~~\n\n\nRULES\n\n$rules"
matchs=""

while IFS= read -r line; do
	
    rule1=$(echo "$line" | awk -F',' '{print $1}')
    rule2=$(echo "$line" | awk -F',' '{print $2}')
    rule3=$(echo "$line" | awk -F',' '{print $3}')
    rule4=$(echo "$line" | awk -F',' '{print $4}')
    match=$(echo "$packets" | ./firewall.exe "$rule1" | ./firewall.exe "$rule2" | ./firewall.exe "$rule3" | ./firewall.exe "$rule4")
        matchs+="${match}"$'\n'
	#echo "$match"
	#echo -e "\n\nnewnewnew\n\n"
    
done <<< "$rules"

#for all bg processes will finish
#wait

#echo -e "\n\n!!!!!~~~~~~~~~~~!!!!!!!!!!\n\n"
#echo "$matchs" | wc -l

#output=$(printf "%s\n" "${matchs[@]}")

sorted=$(echo "$matchs" | sort | uniq | sed -e 's/ //g' -e '/^ *$/d')

echo "$sorted"


#for every complex rule the call move in pipe

#awk -F':' '{ print $1}' filename


#sed -e 's/#.*//' -e '/^$/d' test0-rules.in -> del '#' till the end of line

#read x -> read line from stdin to x


#every line in rules_file is complex rule contain:
#rule-1, rule-2, rule-3, rule-4
#variants:
#	matchs - holds the packets that alredy match a complex rule
#	packets - all the packets from stdin
#	cur_matchs - holds the packets that alredy match the rules that checked from the complex rule
#flow line:
#	save stdin in var packets
#	for every line in rules_file:
#		check match on packets for rule-1 and store them in var cur_matchs
#		check match for the other rules on cur_matchs
#		del all lines that in cur_matchs from packets
#		add cur_matchs to matchs
#	sort-uniq and echo matchs to stdout

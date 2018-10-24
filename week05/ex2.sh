printf "0\n" > data.txt

while true
do
	if `ln data.txt data.txt.lock`; then
		lastnum=$(tail -n 1 data.txt.lock)
		printf "$((lastnum+1))\n" >> data.txt.lock
		rm data.txt.lock
	fi
done

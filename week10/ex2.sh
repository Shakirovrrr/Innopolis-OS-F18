FILEDIR='../week01/_file.txt'
printf "Some contents of _file.txt\n" > $FILEDIR
link $FILEDIR '_ex2.txt' > 'ex2.txt'
INODENUM=$(ls -i $FILEDIR | awk '{print $1}')
find ../ -inum $INODENUM >> 'ex2.txt'
find ../ -inum $INODENUM -exec rm {} \; >> 'ex2.txt'
printf "Some contents of _ex3.txt\n" > _ex3.txt
chmod ugo+rw _ex3.txt > ex3.txt
chmod uo+rwx _ex3.txt >> ex3.txt
CURRENTPERMISSION=$(stat -c "%a" _ex3.txt)
chmod $(($CURRENTPERMISSION/100*100 + $CURRENTPERMISSION/100*10 + $CURRENTPERMISSION%10)) _ex3.txt >> ex3.txt
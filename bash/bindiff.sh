d1=$(mktemp /tmp/dump.XXXXXXXXX)
d2=$(mktemp /tmp/dump.XXXXXXXXX)

hexdump $1 > $d1
hexdump $2 > $d2

vimdiff $d1 $d2

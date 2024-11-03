# makes sure main code works by checking it againsed the test cases. Yours and the given ones win and lose
./hangman  "thequick brown .fox jumped "> myout.txt
echo 0 > supposed.txt
diff myout.txt supposed.txt
if [ $? -ne 0 ]; then
    echo "something went wrong with test.sh, Bad!"
    rm supposed.txt
    rm myout.txt
    exit 1
fi

rm supposed.txt
rm myout.txt
exit 0


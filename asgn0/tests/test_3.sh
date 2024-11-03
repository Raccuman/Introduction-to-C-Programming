## testing for valid number range (does it throw an error when its too big?)
./calc -513 10 > badput.txt
if [ $? -eq 0 ]; then
	echo "lets large values slide, bad!"
	rm badput.txt
	exit 1
fi

./calc 513 10 > badput.txt
if [ $? -eq 0 ]; then
        echo "lets large values slide, bad!"
        rm badput.txt
        exit 1
fi

./calc 10 -513 > badput.txt
if [ $? -eq 0 ]; then
        echo "lets large values slide, bad!"
        rm badput.txt
        exit 1
fi

./calc 0 513 > badput.txt
if [ $? -eq 0 ]; then
        echo "lets large values slide, bad!"
        rm badput.txt
        exit 1
fi

## testing error message
./calc 513 10 > badput.txt
echo "TOO BIG" > pear.txt
diff badput.txt pear.txt
if [ $? -eq 1 ]; then
        echo "Incorrect error msg for range, bad!"
        rm badput.txt
	rm pear.txt
        exit 1
fi

./calc -513 10 > badput.txt
echo "TOO BIG" > pear.txt
diff badput.txt pear.txt
if [ $? -eq 1 ]; then
        echo "Incorrect error msg for range, bad!"
        rm badput.txt
        rm pear.txt
        exit 1
fi

./calc 10 513 > badput.txt
echo "TOO BIG" > pear.txt
diff badput.txt pear.txt
if [ $? -eq 1 ]; then
        echo "Incorrect error msg for range, bad!"
        rm badput.txt
        rm pear.txt
        exit 1
fi

./calc 10 -513 > badput.txt
echo "TOO BIG" > pear.txt
diff badput.txt pear.txt
if [ $? -eq 1 ]; then
        echo "Incorrect error msg for range, bad!"
        rm badput.txt
        rm pear.txt
        exit 1
fi
############################################
# Prints a message on success
echo "range failed succsesfully :)"

# time to leave
rm badput.txt
rm pear.txt
exit 0


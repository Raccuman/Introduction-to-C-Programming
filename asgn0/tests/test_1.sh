##############################################
#you need to figure out how to check for bad inputs
# then make the tests for the formatting, those are EZ

## checking for 2 inputs error ( if 2 ints are not inputted, it should throw an error )
./calc 3 
if [ $? -eq 0 ]; then
	echo "Did not throw 1 input error, bad!"
	exit 1
fi

./calc 
if [ $? -eq 0 ]; then
        echo "Did not throw 0 input error, bad!"
        exit 1
fi


./calc 3 > badput.txt
echo "NOT ENOUGH INPUT" > compair.txt
diff badput.txt compair.txt
if [ $? -eq 1 ]; then
        echo "incorrect text output????????"
        rm badput.txt
	rm compair.txt
        exit 1
fi

./calc > badput.txt
echo "NOT ENOUGH INPUT" > compair.txt
diff badput.txt compair.txt
if [ $? -eq 1 ]; then
        echo "incorrect text output????????"
        rm badput.txt
        rm compair.txt
        exit 1
fi
#############################################
# Prints a message on success
echo "# of inputs failed sucsessfully :)"

# Cleans up files created
rm badput.txt
rm compair.txt

exit 0


##############################################
#you need to figure out how to check for bad inputs
# then make the tests for the formatting, those are EZ

## double 0 in front error

./calc 6 3 > badput.txt
echo 0009 > I.txt
diff I.txt badput.txt
if [ $? -eq 0 ]; then
	echo "Printed with two 0's in front, bad!"
	rm I.txt
	rm badput.txt
	exit 1
fi

#############################################
# prints with a space in front error
./calc 3 6 > badput.txt
echo "   9" > AM.txt
diff AM.txt badput.txt
if [ $? -eq 0 ]; then
        echo "Printed with a space in front, bad!"
        rm AM.txt
        rm badput.txt
        exit 1
fi

#############################################
# prints with a space in front error
./calc 3 6 > badput.txt
echo 9 > A.txt
diff A.txt badput.txt
if [ $? -eq 1 ]; then
        echo "Did not calculate correct number, bad!"
        rm A.txt
        rm badput.txt
        exit 1
fi

#############################################
# sucsess message
echo "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"

# Cleans up files created
rm I.txt
rm AM.txt
rm A.txt
rm badput.txt
exit 0


##############################################
#you need to figure out how to check for bad inputs
# then make the tests for the formatting, those are EZ

## checking for numerical input (if to takes words its bad)
./calc hello world > badput.txt
if [ $? -eq 0 ]; then
        echo "Let word input slide, bad!"
        rm badput.txt
        exit 1
fi
###################################
# random error fishing
./calc hello 5 > badput.txt
if [ $? -eq 0 ]; then
        echo "Let word input slide, bad!"
        rm badput.txt
        exit 1
fi

./calc 5 world > badput.txt
if [ $? -eq 0 ]; then
        echo "Let word input slide, bad!"
        rm badput.txt
        exit 1
fi

./calc 5.88 3.66 > badput.txt
if [ $? -eq 0 ]; then
        echo "Let word input slide, computed floats, bad!"
        rm badput.txt
        exit 1
fi

#####################################
## checking error message
echo "BAD INPUT" > pear.txt
diff badput.txt pear.txt
if [ $? -eq 1 ]; then
        echo "Incorrect word error message, bad!"
        rm badput.txt
	rm pear.txt
        exit 1
fi

./calc 5.55 6.66 > badput.txt
diff badput.txt pear.txt
if [ $? -eq 1 ]; then
        echo "Incorrect word error message, bad!"
        rm badput.txt
        rm pear.txt
        exit 1
fi

./calc hello 6 > badput.txt
diff badput.txt pear.txt
if [ $? -eq 1 ]; then
        echo "Incorrect word error message, bad!"
        rm badput.txt
        rm pear.txt
        exit 1
fi

./calc 5 hello > badput.txt
diff badput.txt pear.txt
if [ $? -eq 1 ]; then
        echo "Incorrect word error message, bad!"
        rm badput.txt
        rm pear.txt
        exit 1
fi
############################################
# Prints a message on success
echo "word failed succsesfully :)"

# time to leave
rm badput.txt
rm pear.txt
exit 0


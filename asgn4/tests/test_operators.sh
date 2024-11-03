#!/bin/bash
# Test for addition
echo "3 2 + " | ../calc > output.txt
echo "5.0000000000" > expected.txt
diff output.txt expected.txt
if [ $? -eq 1 ]; then
    echo "Addition test failed!"
    rm output.txt
    rm expected.txt
    exit 1
fi

# Test for subtraction
echo "3 2 - " | ../calc > output.txt
echo "1.0000000000" > expected.txt
diff output.txt expected.txt
if [ $? -eq 1 ]; then
    echo "Subtraction test failed!"
    rm output.txt
    rm expected.txt
    exit 1
fi

# Test for multiplication
echo "3 2 * " | ../calc > output.txt
echo "6.0000000000" > expected.txt
diff output.txt expected.txt
if [ $? -eq 1 ]; then
    echo "Multiplication test failed!"
    rm output.txt
    rm expected.txt
    exit 1
fi

# Test for division
echo "4 2 / " | ../calc > output.txt
echo "2.0000000000" > expected.txt
diff output.txt expected.txt
if [ $? -eq 1 ]; then
    echo "Division test failed!"
    rm output.txt
    rm expected.txt
    exit 1
fi

echo "All operator tests passed successfully :)"
rm output.txt
rm expected.txt
exit 0

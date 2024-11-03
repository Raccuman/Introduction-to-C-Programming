echo "hey there man, whatcha got goin on there?" > test_test.txt
./xd test_test.txt > badput.txt
if [ $? -ne 0 ]; then
        echo "had issues with a good file, Bad!"
        rm badput.txt
        exit 1
fi
rm badput.txt
rm test_test.txt
exit 0
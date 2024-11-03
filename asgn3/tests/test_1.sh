./xd hey there > badput.txt
if [ $? -ne 1 ]; then
        echo "Let in > 1 argument in, Bad!"
        rm badput.txt
        exit 1
fi
rm badput.txt
exit 0
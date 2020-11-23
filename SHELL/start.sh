cd ./command/wh/
bash ./gcc_wh.sh

cd ../lsb
bash ./gcc_lsb.sh

cd ../hzh
bash ./gcc_hzh.sh

cd ../..
gcc main.c -o main
echo "success!"


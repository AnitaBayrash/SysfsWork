make >> logger.txt
sudo insmod ./timer.ko
echo "Test: timer_period = 0.5 sec.:"
echo 500 >> /sys/timer/timer_period
sleep 2
dmesg | tail -n 10
sudo rmmod timer
make clean >> logger.txt

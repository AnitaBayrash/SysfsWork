make >> logger.txt
sudo insmod ./timer.ko

echo "Test: timer_period = 0.5 sec.:"
echo 500 >> /sys/timer/timer_period
sleep 2
dmesg | tail -n 5

echo "Test: timer_period = 1 sec.:"
echo 1000 >> /sys/timer/timer_period
sleep 3
dmesg | tail -n 5

sudo rmmod timer
make clean >> logger.txt

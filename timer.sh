make >> logger.txt
sudo insmod ./timer.ko
echo 500 >> /sys/timer/timer_period
cat /sys/timer/timer_period
sudo rmmod timer
make clean >> logger.txt

#! /bin/sh
x=0;
for i in {1..20}
do
	y=$(./philo_bonus 200 410 200 200 3 | grep died | wc -l)
	x=$((x + y))
done
echo $x
#
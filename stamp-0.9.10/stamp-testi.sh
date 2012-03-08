#!/bin/bash

######  EXECUTION IDENTIFIER  ######
# Get command line paramter or the current date if it misses
if [ $# -gt 0 ]; then
    task=$1
else
	echo "please give me a task! (error)"
    exit
fi

prefix="etlsMpi"

export STM_STATS="y"

mode="real"
#mode="sim"

if [ $mode == "sim" ] ; then
######   STAMP SIM BENCHMARKS   ######
bayes="./bayes/bayes -v32 -r1024 -n2 -p20 -s0 -i2 -e2 -t"
genome="./genome/genome -g256 -s16 -n16384 -t"
intruder="./intruder/intruder -a10 -l4 -n2038 -s1 -t" 
kmeanslow="./kmeans/kmeans -m40 -n40 -t0.05 -i kmeans/inputs/random2048-d16-c16.txt -p"
kmeanshigh="./kmeans/kmeans -m15 -n15 -t0.05 -i kmeans/inputs/random2048-d16-c16.txt -p"
labyrinth="./labyrinth/labyrinth -i labyrinth/inputs/random-x32-y32-z3-n96.txt -t"
ssca2="./ssca2/ssca2 -s13 -i1.0 -u1.0 -l3 -p3 -t"
vacationlow="./vacation/vacation -n2 -q90 -u98 -r16384 -t4096 -c"
vacationhigh="./vacation/vacation -n4 -q60 -u90 -r16384 -t4096 -c"
yada="./yada/yada -a20 -i yada/inputs/633.2 -t"
else
######   STAMP REAL BENCHMARKS   ######
bayes="./bayes/bayes -v32 -r4096 -n10 -p40 -i2 -e8 -s1 -t"
genome="./genome/genome -g16384 -s64 -n16777216 -t"
intruder="./intruder/intruder -a10 -l256 -n524288 -s1 -t100 -i" 
kmeanslow="./kmeans/kmeans -m40 -n40 -t0.00001 -i kmeans/inputs/random-n65536-d32-c16.txt -p"
kmeanshigh="./kmeans/kmeans -m15 -n15 -t0.00001 -i kmeans/inputs/random-n65536-d32-c16.txt -p"
labyrinth="./labyrinth/labyrinth -i labyrinth/inputs/random-x1024-y1024-z11-n1024.txt -t"
ssca2="./ssca2/ssca2 -s20 -i1.0 -u1.0 -l3 -p3 -t"
vacationlow="./vacation/vacation -n2 -q90 -u98 -r10485760 -t41943040 -w30000 -c"
vacationhigh="./vacation/vacation -n4 -q60 -u90 -r10485760 -t41943040 -c"
vacationveryhigh="./vacation/vacation -n8 -q60 -u90 -r10485760 -t41943040 -c"
yada="./yada/yada -a15 -i yada/inputs/ttimeu1000000.2 -t"
fi

for threads in {1..56}
#for threads in 96
do

	logdir="logs/$task"
	logfile="$prefix.$threads.log"

        # Creating directory if not exists
	mkdir -p $logdir

        
        # Check if this task already exists
	if [ -f "$logdir/$logfile" ] ; then
	    echo "$logdir/$logfile already exists."
	    continue
	fi

	for runs in {1..10}
	do
	    eval cmd=\$$task
	    echo "Executing: ${cmd} ${threads}" | tee -a $logdir/$logfile
	    $cmd $threads 1>>$logdir/$logfile 2>&1
    done
done

exit


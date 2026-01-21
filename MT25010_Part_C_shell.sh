#!/bin/bash

CSV_FILE="MT25010_Part_C_CSV.csv"

# write CSV header
echo "Program,Worker,Avg_CPU_Percent,Disk_Read_kBps,Disk_Write_kBps,Time_sec" > $CSV_FILE

PROGRAMS=("A" "B")
WORKERS=("cpu" "mem" "io")

for prog in "${PROGRAMS[@]}"; do
  for work in "${WORKERS[@]}"; do

    if [ "$prog" == "A" ]; then
      CMD="./programA $work"
      PNAME="ProgramA"
    else
      CMD="./programB $work"
      PNAME="ProgramB"
    fi

    echo "Running $PNAME + $work"

    # ---- start program (pinned to CPU 0) ----
    taskset -c 0 $CMD &
    PID=$!

    # ---- collect CPU usage (top) ----
    CPU_SUM=0
    CPU_COUNT=0

    while kill -0 $PID 2>/dev/null; do
      CPU_VAL=$(top -b -n 1 | awk -v pid=$PID '$1==pid {print $9}')
      if [ ! -z "$CPU_VAL" ]; then
        CPU_SUM=$(echo "$CPU_SUM + $CPU_VAL" | bc)
        CPU_COUNT=$((CPU_COUNT + 1))
      fi
      sleep 1
    done

    if [ $CPU_COUNT -eq 0 ]; then
      AVG_CPU=0
    else
      AVG_CPU=$(echo "scale=2; $CPU_SUM / $CPU_COUNT" | bc)
    fi

    # ---- disk IO using iostat ----
    IO_STATS=$(iostat -dk 1 2 | awk 'NR>6 {r+=$3; w+=$4} END {print r,w}')
    DISK_READ=$(echo $IO_STATS | awk '{print $1}')
    DISK_WRITE=$(echo $IO_STATS | awk '{print $2}')

    # ---- execution time ----
    TIME_VAL=$( (/usr/bin/time -f "%e" taskset -c 0 $CMD) 2>&1 >/dev/null )

    # ---- append to CSV ----
    echo "$PNAME,$work,$AVG_CPU,$DISK_READ,$DISK_WRITE,$TIME_VAL" >> $CSV_FILE

    echo "Done: $PNAME + $work"
    echo "--------------------------------"

  done
done

echo "All experiments completed."

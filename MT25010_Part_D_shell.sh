#!/bin/bash

CSV_FILE="MT25010_Part_D_CSV.csv"
echo "Program,Worker,Count,CPU_Usage,Time_sec" > $CSV_FILE

WORKERS=("cpu" "mem" "io")

measure_cpu() {
    top -b -n 2 -d 0.5 | grep "%Cpu" | tail -1 | awk '{print 100 - $8}'
}

# -------- Program A --------
for COUNT in 2 3 4 5
do
  for WORK in "${WORKERS[@]}"
  do
    echo "ProgramA | $WORK | processes=$COUNT"

    CPU=$(measure_cpu)
    TIME_VAL=$( (/usr/bin/time -f "%e" taskset -c 0 ./programA $WORK $COUNT) 2>&1 >/dev/null )

    echo "ProgramA,$WORK,$COUNT,$CPU,$TIME_VAL" >> $CSV_FILE
  done
done

# -------- Program B --------
for COUNT in 2 3 4 5 6 7 8
do
  for WORK in "${WORKERS[@]}"
  do
    echo "ProgramB | $WORK | threads=$COUNT"

    CPU=$(measure_cpu)
    TIME_VAL=$( (/usr/bin/time -f "%e" taskset -c 0 ./programB $WORK $COUNT) 2>&1 >/dev/null )

    echo "ProgramB,$WORK,$COUNT,$CPU,$TIME_VAL" >> $CSV_FILE
  done
done

echo "Part D completed."

#!/usr/bin/env bash

if [[ $# -lt 1 ]]; then
  echo "Usage: $0 cmd"
  exit
fi
if [[ $# -gt 1 ]]; then
  echo "Usage: $0 cmd"
  exit
fi

avg=0;
iterations=100
for ((i=1; i <= $iterations; i++)); do
  echo "Iteration: $i"
  ts=$(date +%s%N) ; $1 ; tt=$((($(date +%s%N) - $ts)/1000000)) ; echo "Time taken: $tt milliseconds"
  avg=$(($avg + $tt))
done
avg=$(($avg/$i))
echo "Average time taken: $avg ms"

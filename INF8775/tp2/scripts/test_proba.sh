#!/bin/bash

count=0
cd ..
while [ $count -lt 10 ]; do
  # Your code or commands to be executed in the loop go here
  echo "Loop iteration $count"
  ./tp.sh -a proba -p -t -e "/Users/mazilious/git/INF8775/tp2/samples/sample_10000_2.txt"
  ((count++))
done

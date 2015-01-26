#!/bin/bash

printf "\n"
echo "Hashset testing."

FILES="input/alphabet.txt input/lines.txt input/midsummer.txt input/plurals.txt input/scene1.txt"

for f in $FILES
do
  printf "\n----------------------------------------\n\n\t"
  echo "Processing $f file..."
  printf "\n"
  ./prog $f .75
done
#!/bin/bash

exprList=(
  "24+42" 
  "3*(2+0)"
  "3+5*(3-(5+2))-3"
  "3+5*(3-(5+2))--3"
  "3+5*(3-(5+2))+-3"
  "3+5*(3-(-5+2))+3"
  "3+5*(3-(-5+2))/3"
  "3+5*(3-(-5/2))-3"
  "0-3"
  "0/3"
  "3-0")

for i in "${exprList[@]}"
do
  echo "Computing " $i
  bcRes=$(echo $i | bc)
  bistroRes=$(echo $i | ./bistro.exec)
  echo "BC result : $bcRes"
  echo "Bistro result : $bistroRes"
  
  if [ "$bcRes" != "$bistroRes" ]
  then
    echo "Failed : $i"
  else
    echo "Success : $i"
  fi
  echo ""
done
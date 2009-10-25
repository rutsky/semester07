#!/bin/bash

function gcd {
  a=$1
  b=$2
  while [ $a -gt 0 ]; do
    c=$a
    a=$[$b % $a]
    b=$c
  done
  
  return $c
}

gcd 42 56
echo $?

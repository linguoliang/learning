#!/bin/bash

count=10000

while [[ $count -gt 0 ]]; do
  # echo "'./a.out'"
  ./a.out
  let count=$count-1
done

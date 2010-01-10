#!/bin/bash

# 1.7. [1] Напишите скрипт, отыскивающий в каталоге все файлы, не принадлежащие
#      указанному пользователю, и выводящий список таких файлов (включая путь к
#      ним), сведения о владельце и группе таких файлов, а также правах доступа
#      для них. По умолчанию скрипт должен отыскивать файлы, не принадлежащие
#      запускающему скрипт пользователю и находящиеся в его домашнем каталоге.

HOME_DIR=~

function printHelp
{
  echo "Usage:"
  echo " $0 [directory]"
}

if [ "$#" == 1 ]; then
  if [ "$1" == "-h" ] || [ "$1" == "--help" ]; then
    printHelp
    exit 0
  elif [ "$#" == 1 ]; then
    HOME_DIR=$1
  fi
elif [ "$#" -gt 1 ]; then
  echo "Error: too much arguments."
  exit 0
fi

echo "Searching in '"$HOME_DIR"'"

find "$HOME_DIR" -type f ! -uid `id -u` -printf 'File: %h/%f, user: %u, group: %g, permissions: %M \n'


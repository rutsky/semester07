#!/bin/bash
# task_1_10.sh
# Task 1.10 on Unix course.
# Vladimir Rutsky <altsysrq@gmail.com>
# 20.12.2009

#HOME_DIR=~
HOME_DIR=~/public/semester07

function print_usage
{
  echo "Usage:"
  echo "  $0 -h, --help                  - print help and exit"
  echo "  $0 directory1 [directory1 ...]"
}

function process_dir
{
  if [ ! -d "$1" ]; then
    echo "Directory '$1' doesn't exists."
    exit 1
  fi
  
  PREV_HASH=
  PREV_BASENAME=
  PREV_FILE=
  find "$1" -type f -exec /bin/sh -c "md5sum '{}' | awk '{print \$1}' | tr -d '\n'" \; -printf '\0%f\0%P\n' | sort | tr '\0' '\n' | \
  while true; do
    if [ "$PREV_HASH" != "" ] && [ "$HASH" == "$PREV_HASH" ] && [ "$BASENAME" == "$PREV_BASENAME" ]; then
      echo "Similar files:"
      echo $PREV_FILE
      while [ "$HASH" == "$PREV_HASH" ] && [ "$BASENAME" == "$PREV_BASENAME" ]; do
        echo $FILE
        read HASH && read BASENAME && read FILE || break 2
      done
    fi
    
    PREV_HASH=$HASH
    PREV_BASENAME=$BASENAME
    PREV_FILE=$FILE
    read HASH && read BASENAME && read FILE || break
  done
}

if [ $# == 0 ]; then
  process_dir "$HOME_DIR"
elif [ "$1" == "-h" ] || [ "$1" == "--help" ]; then
  print_usage
  exit 0
else
  while [ "$1" != "" ]; do
    process_dir "$1"
    shift
  done
fi

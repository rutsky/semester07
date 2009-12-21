#!/bin/bash
# task_1_09.sh
# Task 1.09 on Unix course.
# Vladimir Rutsky <altsysrq@gmail.com>
# 20.12.2009

function print_usage
{
  echo "Usage:"
  echo "  $0 -h, --help               - print help and exit"
  echo "  $0 directory1 directory2"
  echo "  $0 -- directory1 directory2"
}

if (( $# <= 1 )) || [ "$1" == "-h" ] || [ "$1" == "--help" ] || ([ "$1" == "--" ] && (( $# == 2 ))); then
  print_usage
  exit 0
else
  if [ "$1" == "--" ]; then
    shift
  fi
  if [ ! -d $1 ]; then
    echo "Error: Directory '$1' doesn't exists."
    exit 1
  fi
  if [ ! -d $2 ]; then
    echo "Error: Directory '$2' doesn't exists."
    exit 1
  fi

  DIR1_LISTING=`mktemp`
  DIR2_LISTING=`mktemp`
  find "$1" -type f -printf "%P\n" | sort > $DIR1_LISTING
  find "$2" -type f -printf "%P\n" | sort > $DIR2_LISTING
  
  ONLY_IN_1="`comm -23 $DIR1_LISTING $DIR2_LISTING`"
  if (( ${#ONLY_IN_1} != 0 )); then
    echo "Files only in '$1' directory:"
    echo $ONLY_IN_1
  fi
  
  echo "Files only in '$2' directory:"
  comm -13 $DIR1_LISTING $DIR2_LISTING
  
  echo "Distinguishing files:"
  comm -12 $DIR1_LISTING $DIR2_LISTING | \
  while read FILE; do
    if ! cmp -s $1/$FILE $2/$FILE; then
      echo $FILE
    fi
  done
  
  rm -f $DIR1_LISTING $DIR2_LISTING
fi

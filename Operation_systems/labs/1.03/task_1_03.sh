#!/bin/bash
# task_1_03.sh
# Task 1.03 on Unix course.
# Vladimir Rutsky <altsysrq@gmail.com>
# 20.12.2009

SIZE=+1M
#HOME_DIR=~
HOME_DIR=~/public/semester07

function print_usage
{
  echo "Usage:"
  echo "  $0 [options] directory1 [[options] directory1 ...]"
  echo "     -h, --help    - print help and exit"
  echo "     --size=value  - size lower bound (as in find's \`-size' parameter)"
}

PROCESSED=0
function process_dir
{
  PROCESSED=1

  if [ ! -d "$1" ]; then
    echo "Directory '$1' doesn't exists."
    exit 1
  fi
  
  find "$1" -type f -size $SIZE -printf '%h%f %s %u\n'
}

while [ "$1" != "" ]; do
  case $1 in
    -h|--help)
        print_usage
        exit 0
        ;;
    --size=?*)
        SIZE=${1#--size=}
        shift
        ;;
    --)
        shift
        while [ "$1" != "" ]; do
          process_dir "$1"
          shift
        done
        ;;
    *)
        process_dir "$1"
        shift
        ;;
  esac
done

if [ $PROCESSED == 0 ]; then
  process_dir "$HOME_DIR"
fi

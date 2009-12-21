#!/bin/bash
# task_1_01.sh
# Task 1.01 on Unix course.
# Vladimir Rutsky <altsysrq@gmail.com>
# 20.12.2009

SIZE_LOWER_BOUND=+100k
LAST_ACCESS_TIME_PERIOD=+30
#HOME_DIR=~
HOME_DIR=~/public/semester07
ARCHIVE_NAME=$HOME_DIR/archive.tar.gz

function print_usage
{
  echo "Usage:"
  echo "  $0 [options]"
  echo "     -h, --help    - print help and exit"
  echo "     --size=value  - size lower bound (as in find's \`-size' parameter)"
  echo "     --atime=value - access time period (as in find's \`-atime' parameter)"
}

while [ "$1" != "" ]; do
  case $1 in
    -h|--help)
        print_usage
        exit 0
        ;;
    --size=?*)
        SIZE_LOWER_BOUND=${1#--size=}
        shift
        ;;
    --atime=?*)
        LAST_ACCESS_TIME_PERIOD=${1#--atime=}
        shift
        ;;
    *)
        echo "Error: invalid argument '$1'."
        print_usage
        exit 1
        ;;
  esac
done

find "$HOME_DIR" -type f -size $SIZE_LOWER_BOUND -atime $LAST_ACCESS_TIME_PERIOD -not -wholename "$ARCHIVE_NAME" -print0 | xargs -0 tar -czf "$ARCHIVE_NAME"

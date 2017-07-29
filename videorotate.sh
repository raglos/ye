#!/bin/bash

if [[ -z "$1" || -z "$2" || -z "$3" ]]; then
    echo "usage: ""$0"" <input file> <output file> <degrees to rotate (clock-wise)>";
    exit 1;
fi

FFMPEG=$(which ffmpeg)

# ffmpeg is not installed
if [[ ${#FFMPEG} -lt 2 ]]; then
    echo "install ffmpeg";
    exit 1;
fi

ffmpeg -i "$1" -c copy -metadata:s:v:0 rotate="$3" "$2"

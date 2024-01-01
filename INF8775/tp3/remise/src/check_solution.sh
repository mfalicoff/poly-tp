#!/bin/bash

path_to_file=""

while getopts "e:p" opt; do
    case "$opt" in
        e)
            path_to_file="$OPTARG"
            ;;
        *)
            usage
            ;;
    esac
done

(gtimeout 180s ./tp.sh -e "$path_to_file" -p; exit 0) | ./check_sol.py -e "$path_to_file" -s sortie.out

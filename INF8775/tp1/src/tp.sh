#!/bin/bash

algorithm=""
path_to_file=""
print_sorted=false
print_execution_time=false

usage() {
    echo "Usage: $0 -a [counting | quick | quickSeuil | quickRandomSeuil] -e [path_to_file] [-p] [-t]"
    exit 1
}

while getopts "a:e:pt" opt; do
    case "$opt" in
        a)
            algorithm="$OPTARG"
            ;;
        e)
            path_to_file="$OPTARG"
            ;;
        p)
            print_sorted=true
            ;;
        t)
            print_execution_time=true
            ;;
        *)
            usage
            ;;
    esac
done

if [[ ! "$algorithm" =~ ^(counting|quick|quickSeuil|quickRandomSeuil)$ ]]; then
    echo "Error: Invalid algorithm option. Please specify one of: counting, quick, quickSeuil, quickRandomSeuil"
    usage
fi

if [[ ! "$path_to_file" = /* ]]; then
    echo "Error: The path to the file must be an absolute path."
    usage
fi

if [ "$print_sorted" = "false" ]; then
  print_option=""
else
  print_option="-p"
fi

if [ "$print_execution_time" = "false" ]; then
  t_option=""
else
  t_option="-t"
fi

echo "Running $algorithm algorithm on file $path_to_file with params $print_sorted $print_execution_time"
python main.py -a "$algorithm" -e "$path_to_file" "$print_option" "$t_option"
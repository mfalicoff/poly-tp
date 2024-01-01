#!/bin/bash

path_to_file=""
print_solutions=false

usage() {
    echo "Usage: $0 -e [path_to_file] [-p]"
    exit 1
}

# Continue with the script, regardless of whether dependencies were just installed or were already installed
while getopts "e:p" opt; do
    case "$opt" in
        e)
            path_to_file="$OPTARG"
            ;;
        p)
            print_solutions=true
            ;;
        *)
            usage
            ;;
    esac
done

if [[ ! "$path_to_file" = /* ]]; then
    echo "Error: The path to the file must be an absolute path."
    usage
fi

if [ "$print_solutions" = "false" ]; then
    print_solutions=""
else
    print_solutions="-p"
fi

python main.py -e "$path_to_file" $print_solutions

#!/bin/bash

algorithm=""
path_to_file=""
print_boxes=false
print_execution_time=false
print_height=false

usage() {
    echo "Usage: $0 -a [glouton | progdyn | proba] -e [path_to_file] [-p] [-t] [-z]"
    exit 1
}

# Checking if SciPy and NumPy are not installed
if ! python -c "import scipy, numpy" &> /dev/null; then
    # Displaying text
    echo "SciPy and NumPy are not installed."

    # Waiting for Enter to be pressed
    read -p "Press Enter to continue to install the required packages..."

    echo "Installing SciPy and NumPy..."

    # Installing SciPy and NumPy
    pip install -r requirements.txt
fi

# Continue with the script, regardless of whether dependencies were just installed or were already installed
while getopts "a:e:ptz" opt; do
    case "$opt" in
        a)
            algorithm="$OPTARG"
            ;;
        e)
            path_to_file="$OPTARG"
            ;;
        p)
            print_boxes=true
            ;;
        t)
            print_execution_time=true
            ;;
        z)
            print_height=true
            ;;
        *)
            usage
            ;;
    esac
done

if [[ ! "$algorithm" =~ ^(glouton|progdyn|proba)$ ]]; then
    echo "Error: Invalid algorithm option. Please specify one of: glouton progdyn proba"
    usage
fi

if [[ ! "$path_to_file" = /* ]]; then
    echo "Error: The path to the file must be an absolute path."
    usage
fi

if [ "$print_boxes" = "false" ]; then
    print_option=""
else
    print_option="-p"
fi

if [ "$print_execution_time" = "false" ]; then
    t_option=""
else
    t_option="-t"
fi

if [ "$print_height" = "false" ]; then
    height_option=""
else
    height_option="-z"
fi

echo "Running $algorithm algorithm on file $path_to_file with params $print_boxes $print_execution_time $print_height"
python main.py -a "$algorithm" -e "$path_to_file" "$print_option" "$t_option" "$height_option"

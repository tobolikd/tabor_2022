#!/bin/bash

# COLORS
NO_COLOR='\033[0m'        # Text Reset
GREEN='\033[0;32m'        # Green
YELLOW='\033[0;33m'       # Yellow


# compile project
printf "\n$(GREEN)Compilining project$(NO_COLOR)\n"
make || (print_exitcodes && exit 1)
printf "$(GREEN)DONE$(NO_COLOR)\n"


# run project
printf "\n$(GREEN)Running project$(NO_COLOR)\n"
# destroy everything living
./output/make purge

chmod +x log_generator || (print_exitcodes && exit 2)
./log_generator || (print_exitcodes && exit 3)
printf "$(GREEN)DONE$(NO_COLOR)\n"


# run make to compile tex files
printf "\n$(GREEN)Compiling tex files in $(YELLOW)./output/$(NO_COLOR)\n"
./output/make || (print_exitcodes && exit 4)
# clean
./output/make clean
printf "$(GREEN)DONE$(NO_COLOR)\n"

print_exitcodes()
{
    echo "Something went wrong, check the exitcode to find out what happened"
    echo ""
    echo "EXIT CODES:"
    echo "1 - compilation fail"
    echo "2 - mode change fail"
    echo "3 - program run fail"
    echo "4 - compiling .tex files failed (check ./output/*.log)"
}
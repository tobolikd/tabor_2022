#!/bin/bash

# COLORS
NO_COLOR='\033[0m'        # Text Reset
GREEN='\033[0;32m'        # Green
YELLOW='\033[0;33m'       # Yellow

# exitcodes help
print_exitcodes()
{
    echo "Something went wrong, check the exitcode to find out what happened"
    echo ""
    echo "EXIT CODES:"
    echo "0 - everything allright"
    echo "1 - compilation fail"
    echo "2 - mode change fail"
    echo "3 - program run fail"
    echo "4 - compiling .tex files failed (check ./output/*.log)"
    return 0
}

# compile project
printf "\n${GREEN}Compiling project${NO_COLOR}\n"
make || (print_exitcodes && exit 1)
printf "${GREEN}DONE${NO_COLOR}\n"


printf "\n${GREEN}Wiping output dir${NO_COLOR}\n"
# destroy everything living
cd ./output
make purge
cd ..
printf "${GREEN}DONE${NO_COLOR}\n"


# run project
printf "\n${GREEN}Running project${NO_COLOR}\n"
chmod +x log_generator || (print_exitcodes && exit 2)
./log_generator || (print_exitcodes && exit 3)
printf "${GREEN}DONE${NO_COLOR}\n"


# run make to compile tex files
printf "\n${GREEN}Compiling tex files in ${YELLOW}./output/${NO_COLOR}\n{\n\n"
cd ./output
make || (print_exitcodes && exit 4)
printf "\n}${GREEN}DONE${NO_COLOR}\n"

# clean
printf "\n${GREEN}Cleaning ${YELLOW}./output/${NO_COLOR}\n{\n\n"
make clean
printf "${GREEN}DONE${NO_COLOR}\n"

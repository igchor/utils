# run.sh
make 2> compiler_out.txt && exit 1
awk -F ":" '{ filename=$1 ; linenumber=$2 ;  charnumber=$3 ; type=$4; if (type == " error") { system("sed -i \""linenumber"s/\\(.\\{"(charnumber-1)"\\}\\)\\(.*\\)/\\1std::\\2/\"g "filename""); exit 0; } }' compiler_out.txt
########################################################


# ./run.sh
# while [ $? -eq 0 ]; do ./run.sh ; done

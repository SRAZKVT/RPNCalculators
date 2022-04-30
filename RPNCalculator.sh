is_number() {
    # TODO: find out why this complains whenever it gets a + and fix it
	if expr "${1}" : '-*[0-9][0-9]*$'>/dev/null; then
		echo true
	else
    	echo false
    fi
}

read calculation
dir=$(ls | paste -sd" ")
star='*'
calculation=$(echo ${calculation} | sed "s/${dir}/\\${star}/g")

stack=""

while [ "${calculation}" ]; do
    token=$(echo "${calculation}" | awk '{print $1}')
    calculation=$(echo "${calculation}" | awk '{$1=""; print $0}')
	
    if [ $(is_number ${token}) = true ]; then
        result=${token}
    else
        # TODO: Check if there are two elements or more on the stack, if less, throw an error
		second=$(echo ${stack} | awk '{print $1}')
		first=$(echo ${stack} | awk '{print $2}')
		stack=$(echo ${stack} | awk '{$1=$2=""; print $0}')

		case ${token} in
    		+)	result=$(echo "${first}+${second}" | bc)
    			;;
			-)	result=$(echo "${first}-${second}" | bc)
				;;
			*)	result=$(echo "${first}*${second}" | bc)
				;;
			/)	result=$(echo "${first}/${second}" | bc)
				;;
			%)	result=$(echo "${first}%${second}" | bc)
				;;
			?)	echo "Unrecognised token : ${token}"
				exit 1
				;;
		esac
	fi
    stack="${result} ${stack}"
done

echo ${stack}

#####################################################################
# PATHs of all NuSMV versions
NuSMV_CTL_ORIG=/opt/NuSMV-2.5.4-x86_64/bin/NuSMV
NuSMV_ARCTL_32=/opt/bin/NuSMV-32bit-2.2.2-ARCTL
NuSMV_ARCTL_64=~/git/bionusmv/NuSMV-a/NuSMV/build/bin/NuSMV

####################################################################
# NuSMV tests specification files
MODEL_CTL_File=pacbb_ctl.smv
CTL_Files="pacbb_ctl01.smv pacbb_ctl02.smv"
MODEL_ARCTL_File=pacbb_arctl.smv
ARCTL_Files="pacbb_arctl01.smv pacbb_arctl02.smv pacbb_arctl03.smv pacbb_arctl04.smv"

####################################################################
# Terminal ANSI colors
G='\033[1;32m'
B='\033[1;34m'
R='\033[0;31m'
N='\033[0m'

function testFiles {
	TMP=tmp.smv
	ARGS=-dcx

	echo -e "$G$2 properties$N"

	for f in $3; do
		echo -e "$B\tTesting: $f $N"
		cat $1 $f > $TMP
		res_orig=`$NuSMV_CTL_ORIG $ARGS $TMP 2> /dev/null | grep "\-\- specification" | rev | cut -d' ' -f1 | rev`
		res_a32=`$NuSMV_ARCTL_32 $ARGS $TMP 2> /dev/null | grep "\-\- specification" | rev | cut -d' ' -f1 | rev`
		res_a64=`$NuSMV_ARCTL_64 $ARGS $TMP 2> /dev/null | grep "\-\- specification" | rev | cut -d' ' -f1 | rev`

		# For ARCTL
		if [ "$2"=="ARCTL" ]; then
			if [ "$res_a32" != "$res_a64" ]; then
				echo -e "$R[$res_a32]$N"
				echo -e "$R[$res_a64]$N"
			fi
		else
			# For CTL
			if [ "$res_orig" != "$res_a64" ]; then
				echo -e "$R[$res_orig]$N"
				echo -e "$R[$res_a64]$N"
			fi
			if [ "$res_orig" != "$res_a32" ]; then
				echo -e "$R[$res_orig]$N"
				echo -e "$R[$res_a32]$N"
			fi
		fi
		rm -f $TMP
	done
}

testFiles $MODEL_CTL_File   "CTL"   "$CTL_Files"

testFiles $MODEL_ARCTL_File "ARCTL" "$ARCTL_Files"


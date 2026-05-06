#!/bin/sh
N_TOT=0
N_SUCC=0

for F in unit*.in; do
    STEM=`echo ${F} | sed 's/..$//'`
    EXE=${STEM}.exe
    EOUT=${STEM}.exp
    diff <( ./${EXE} < ${F} ) ${EOUT}
    if [ $? -eq 0 ]; then
        N_SUCC=`echo "${N_SUCC} + 1" | bc`
    else
        echo "Test ${F} failed"
    fi
    N_TOT=`echo "${N_TOT} + 1" | bc`
done

echo "Passed:   ${N_SUCC}/${N_TOT}"

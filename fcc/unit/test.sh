#!/bin/sh
N_TOT=0
N_SUCC=0

for EXE in unit*.exe; do
    ./${EXE}
    if [ $? -eq 0 ]; then
        N_SUCC=`echo "${N_SUCC} + 1" | bc`
    else
        echo "Test ${F} failed"
    fi
    N_TOT=`echo "${N_TOT} + 1" | bc`
done

echo "Passed:   ${N_SUCC}/${N_TOT}"

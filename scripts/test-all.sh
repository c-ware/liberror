make -f Makefile.dist clean

rm -rf /tmp/test_output
mkdir -p /tmp/test_output
mkdir -p /tmp/test_output/completed
mkdir -p /tmp/test_output/output

function test_on() {
    scripts/vm-tests/$1.sh 2>&1 1> /tmp/test_output/output/$1
    touch /tmp/test_output/completed/$1
}

NUMBER_OF_SCRIPTS=`ls scripts/vm-tests | wc -l`

test_on ultrix          &
test_on 4.3bsd          &
test_on nextstep        &
test_on os2             &
test_on sun-solaris10   &
test_on unixware        &
test_on dragonflybsd    &
test_on openbsd         &
test_on netbsd          &
test_on freebsd         &

while [ ! "`ls /tmp/test_output/completed | wc -l`" = "$NUMBER_OF_SCRIPTS" ]; do
    printf "%s/%s Completed\n" "`ls /tmp/test_output/completed | wc -l`" "$NUMBER_OF_SCRIPTS"
    sleep 1
done

printf "%s/%s Completed\n" "`ls /tmp/test_output/completed | wc -l`" "$NUMBER_OF_SCRIPTS"

# Dump the output of each file to the stdout
for out in /tmp/test_output/output/*; do
    printf "Test output from '%s':\n" $out;
    cat $out | sed 's/^\t//g' | sed 's/^/\t/g';
done

rm -f /tmp/test_log

# Dump the output of each file into a status file
for out in /tmp/test_output/output/*; do
    printf "Test output from '%s':\n" $out >> /tmp/test_log;
    cat $out | sed 's/^\t//g' | sed 's/^/\t/g' >> /tmp/test_log;
done

printf "%s\n" "To reference output again, please see /tmp/test_log"

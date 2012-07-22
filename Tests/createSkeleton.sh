#!/bin/bash

ADODBPATH="../ADOdb"

# Create directories
find $ADODBPATH -type d | sed "s/\.\.\///" | xargs -t mkdir -p

# Generate tests
rgrep -H "class " $ADODBPATH | grep ".php:" | cut -d: -f1 | sed "s/\.php//" | \
	sed "s/^.*\/ADOdb\//ADOdb\//" | \
	awk '$2=$1 {gsub("/","\\\\",$2); print "\\\\"$2" ../"$1".php "$2"Test "$1"Test.php"}' | \
	xargs -t -n4 phpunit-skelgen --bootstrap bootstrap.php --test --

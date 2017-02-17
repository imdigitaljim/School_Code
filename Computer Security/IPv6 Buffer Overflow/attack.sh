#!/bin/bash

perl -e 'print "\n"'|nc6 2601:4c0:4000:e1d8:a00:27ff:fe1c:eb3c 55555
perl -e 'print "A"x10'|nc6 2601:4c0:4000:e1d8:a00:27ff:fe1c:eb3c 55555
perl -e 'print "A"x50'|nc6 2601:4c0:4000:e1d8:a00:27ff:fe1c:eb3c 55555
perl -e 'print "A"x240'|nc6 2601:4c0:4000:e1d8:a00:27ff:fe1c:eb3c 55555
perl -e 'print "A"x240'|nc6 2601:4c0:4000:e1d8:a00:27ff:fe1c:eb3c 55555
perl -e 'print "A"x0'|nc6 2601:4c0:4000:e1d8:a00:27ff:fe1c:eb3c 55555
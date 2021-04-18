#!/bin/perl

use warnings;
use strict;

while(<>) {
    if (/`([^`]+)`\{.include}/) {
        if (-e $1 && open my $fh, '<', $1) {
            local $/;
            print <$fh>;
            close $fh;
        } else {
            print STDERR "failed to include file $1\n";
        }
    } else {
        print $_;
    }
}

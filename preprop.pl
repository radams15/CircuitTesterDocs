#!/bin/perl

use warnings;
use strict;

my $PS_CODE_TEMPLATE = "haskell";

sub read_file{
	my $out = undef;
	
	my ($name) = @_;
	
	if (-e $1 && open(my $fh, '<', $1)) {
            local $/;
            $out = <$fh>;
            close $fh;
        } else {
            print STDERR "failed to include file $1\n";
        }
        
        return $out;
}

while(<>) {
    if (/%\s*include\s*\((.+)\)/) { # include text
	if(my $data = read_file($1)){
		print $data;
	}
    } elsif (/%\s*include_pc\s*\((.+)\)/) { # include pseudocode
    	if(my $data = read_file($1)){
		print "\n``` $PS_CODE_TEMPLATE\n\n$data\n```\n";
	}
    } elsif (/\s*%\s*exec\s*\((.*)\)\s*/){
	print `$1`;
    }else {
        print $_;
    }
}

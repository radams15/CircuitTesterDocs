#!/bin/perl

use warnings;
use strict;

my $PS_CODE_TEMPLATE = "haskell";

sub read_file{
	my $content = "";
	
	my ($name) = @_;
	
	if (-e $1 && open(my $fh, '<', $1)) {
        local $/;
        $content = <$fh>;
        close $fh;
    } else {
        print STDERR "failed to include file $1\n";
    }
    
    $content =~ s/(\@brief)|(\@)|(\Ω)|(\x221E)//g;
    
    return $content;
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
	} elsif (/%\s*include_cpp\s*\((.+)\)/) { # include c++
    	if(my $data = read_file($1)){
            print "\n``` cpp\n\n$data\n```\n";
		}
	} elsif (/%\s*include_py\s*\((.+)\)/) { # include python
    	if(my $data = read_file($1)){
            print "\n``` python\n\n$data\n```\n";
		}
	} elsif (/\s*%\s*exec\s*\((.*)\)\s*/){
        print `$1`;
    } else { # else print the input text
        print $_;
    }
}

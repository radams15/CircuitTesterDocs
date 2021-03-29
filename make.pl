#!/usr/bin/perl

use strict;
use warnings;

use Cwd qw(getcwd);

my @FOLDERS = (
	"Analysis",
	"Journal",
	"Targets",
	#"Design",
);


sub main{
	my $before = getcwd;

	mkdir "build";

	foreach my $folder (@FOLDERS){
		chdir $folder;

		my $command = "perl make.pl";
		`$command`;

		chdir $before;
	}
}

&main;

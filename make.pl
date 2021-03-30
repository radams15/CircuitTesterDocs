#!/usr/bin/perl

use strict;
use warnings;

use Cwd qw(getcwd);

my @FOLDERS = (
	"Analysis",
	"Journal",
	"Targets",
	"Design",
);

my $BUILD_FOLDER = "build";



sub file_write{
    my ($name, $data) = @_;

    open(FH, ">", $name) or die $!;

    print FH $data;

    close(FH);
}


sub main{	
	my $before = getcwd;

	mkdir $BUILD_FOLDER;

	foreach my $folder (@FOLDERS){
		chdir $folder;

		my $command = "perl make.pl";
		`$command`;

		chdir $before;
	}
	
	my $wordcount_data = "";
	foreach my $file (<$BUILD_FOLDER/*.pdf>){		
		my $command = "pdftotext $file - | wc -w";
		
		my $num_words = `$command`;
		chomp $num_words;
		
		$wordcount_data .= "# $file\n\t$num_words\n\n";
	}
	
	file_write("$BUILD_FOLDER/wordcounts.md", $wordcount_data);
}

&main;

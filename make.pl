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

		print "$folder\n";

		my $command = "perl make.pl";
		`$command`;

		chdir $before;
	}
	
	my $wordcount_data = "";
	foreach my $file (<$BUILD_FOLDER/*.pdf>){		
		my $command = "pdftotext $file - | wc -w";
		
		my $num_words = `$command`;
		chomp $num_words;
		
		$wordcount_data .= "<h2>$file</h2><br><p>$num_words<p><br><br>";
	}
	
	file_write("$BUILD_FOLDER/wordcounts.html", $wordcount_data);
}

&main;

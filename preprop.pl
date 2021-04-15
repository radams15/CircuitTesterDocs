#!/bin/perl

use warnings;
use strict;

use Cwd;


sub fread{
	my ($fname) = @_;
	
	open(FH, "<", $fname) or die "Fail to open file!";
	
	my $out = "";
	while(<FH>){
		$out .= $_;
	}
	
	close(FH);
	
	return $out;
}

sub fwrite{
	my ($fname, $data) = @_;
	
	open(FH, ">", $fname) or die "Fail to open file!";
	
	print FH $data;
	
	close(FH);
}

sub process{
	my ($file) = @_;
	
	my $data = fread $file;
	
	while ($data =~ /(%\s*include_script\s*"(.*)")/g) {
		my ($full, $script) = ($1, $2);
		my $script_data = fread($script);
		$data =~ s/$full/\n```\n$script_data\n```\n/;
	}
}

sub main{
	my ($wd, $file) = @_;
	
	if( !defined $wd or !defined $file ){
		die "Needs 2 args, working_dir and file\n";
	}
	
	my $orig_dir = cwd();
	
	chdir $wd;
	
	process $file;
	
	chdir $orig_dir;
}


main(@ARGV);

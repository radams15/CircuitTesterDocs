#!/usr/bin/perl
use strict;
use warnings;

my @ORDER = (
	"targets.md"
);

my $OUT_FILE = "Targets.pdf";

my @EXTS = ("raw_tex", "grid_tables");

my $FONT_SIZE = "12pt";

my $CONTENTS_PAGE = 1;

my $CODE_STYLE = "tango";


sub main{	
	@ORDER = map { "'$_'" } @ORDER;

	my $md_files = join " ", @ORDER;

	my $exts =  join "", (map { "+$_" } @EXTS);

	my $command = "pandoc $md_files -s -V fontsize=$FONT_SIZE -V geometry:margin=1in -s --quiet -f markdown$exts --highlight-style=$CODE_STYLE -o '${OUT_FILE}' -t latex";
	
	print "$command\n";

	`$command`;
	
	`mv $OUT_FILE ../build`;
}


&main;

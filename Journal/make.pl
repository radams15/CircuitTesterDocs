#!/usr/bin/perl

use strict;
use warnings;

my @ORDER = (
	"styling/pagebreak.tex",
	"journal.md",
);

my $OUT_FILE = "Journal.pdf";

my @EXTS = ("raw_tex", "grid_tables");

my $FONT_SIZE = "12pt";

my $CODE_STYLE = "tango";


sub main{	
	@ORDER = map { "'$_'" } @ORDER;

	my $md_files = join " 'styling/border.md' ", @ORDER;

	my $exts =  join "", (map { "+$_" } @EXTS);

	my $command = "pandoc $md_files meta.yaml -s -V fontsize=$FONT_SIZE -V geometry:margin=1in -s --quiet -f markdown$exts --highlight-style=$CODE_STYLE -B before.tex  --toc --toc-depth=2 -o '${OUT_FILE}' -t latex";
	
	print "$command\n";

	`$command`;
	
	`mv $OUT_FILE ../build`;
}


&main;

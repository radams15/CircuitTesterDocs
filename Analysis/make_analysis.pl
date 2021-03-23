#!/usr/bin/perl
use strict;
use warnings;

my @ORDER = ("styling/style.md", "styling/pagebreak.tex", "chap-3/stating the problem.md", "styling/pagebreak.tex", "chap-4/analysis.md");
my $OUT_FILE = "Analysis.pdf";

my $FONT_SIZE = "12pt";

my $CONTENTS_PAGE = 1;

my $CODE_STYLE = "tango";


sub main{	
	@ORDER = map { "'$_'" } @ORDER;

	my $md_files = join(" 'styling/border.md' ", @ORDER);

	my $command = "pandoc $md_files -V fontsize=$FONT_SIZE -s --quiet -f markdown --highlight-style=$CODE_STYLE -B before.tex";
	
	if($CONTENTS_PAGE){
	    $command .= " --toc --toc-depth=1 ";
	}
	
	$command .= " -o '${OUT_FILE}' -t latex";
	
	print "$command\n";

	`$command`;
}


&main;

#!/usr/bin/perl
use strict;
use warnings;

my @ORDER = ("styling/pagebreak.tex", "chap-3/stating the problem.md", "chap-4/analysis.md");
my $OUT_FILE = "analysis.pdf";

my $CSS_FILE = "styling/style.css";

my $CONTENTS_PAGE = 1;

my $CODE_STYLE = "tango";


sub main{
	@ORDER = map { "'$_'" } @ORDER;

	my $md_files = join(" 'styling/border.md' ", @ORDER);

	my $command = "pandoc -s $md_files --quiet -f markdown -t pdf --highlight-style=$CODE_STYLE -B before.tex --css '${CSS_FILE}' -o '${OUT_FILE}'";
	
	if($CONTENTS_PAGE){
	    $command .= " --toc --toc-depth=1";
	}

	#print "$command\n";
	`$command`;
}


&main;

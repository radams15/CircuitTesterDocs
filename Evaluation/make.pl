#!/usr/bin/perl
use strict;
use warnings;

use File::Find;


my @MD_ORDER = (
	"styling/style.md",

	"styling/pagebreak.tex",
	"docs/intro.md",
	
	"styling/pagebreak.tex",
	"docs/testing.md",
	
	"styling/pagebreak.tex",
	"docs/feedback.md",
	
	"styling/pagebreak.tex",
	"docs/success.md",
	
	"styling/pagebreak.tex",
	"docs/usability_features.md",
	
	"styling/pagebreak.tex",
	"docs/maintainence.md",
	
	"styling/pagebreak.tex",
	"docs/future_development.md",
);


my $OUT_FILE = "Evaluation.pdf";

my @EXTS = ("raw_tex", "grid_tables", "fenced_code_blocks", "backtick_code_blocks");

my $CODE_STYLE = "tango.theme";

sub main{
	@MD_ORDER = map { "'$_'" } @MD_ORDER;

	my $md_files = join " 'styling/border.md' ", @MD_ORDER;

	my $exts =  join "", (map { "+$_" } @EXTS);

	my $command = "awk 'FNR==1 && NR!=1 {print \"\\n\"}{print}' $md_files meta.yaml| perl ../preprop.pl | pandoc -s --quiet -f markdown-implicit_figures$exts --highlight-style=$CODE_STYLE -B styling/before.tex --listings -H ../global/header.tex --toc --toc-depth=2 -o '${OUT_FILE}' -t latex";
	
	print "$command\n";

	`$command`;
	
	`mv $OUT_FILE ../build`;
	`rm -rf code`;
}

&main;

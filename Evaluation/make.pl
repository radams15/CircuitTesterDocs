#!/usr/bin/perl
use strict;
use warnings;

use File::Find;


my @MD_ORDER = (
	"styling/style.md",
	
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

	"styling/pagebreak.tex",
	"docs/conclusion.md",
);


my $DIR = "Evaluation";

my $OUT_FILE = "$DIR.pdf";


my @EXTS = ("raw_tex", "grid_tables", "fenced_code_blocks", "backtick_code_blocks");

my $CODE_STYLE = "tango.theme";

sub main{
	@MD_ORDER = map { "'$_'" } @MD_ORDER;

	my $md_files = join " 'styling/border.md' ", @MD_ORDER;

	my $exts =  join "", (map { "+$_" } @EXTS);

	my $command = "echo '\n# $DIR\n' > ../build/$DIR.md && awk 'FNR==1 && NR!=1 {print \"\\n\"}{print}' $md_files| perl ../preprop.pl | sed 's/^#/##/g' | sed 's/images/$DIR\\/images/g' | cat >> ../build/$DIR.md";
	
	print "$command\n";

	print `$command`;
}

&main;

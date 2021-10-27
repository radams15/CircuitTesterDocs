#!/usr/bin/perl
use strict;
use warnings;

my @ORDER = (
	"styling/style.md",
	"styling/pagebreak.tex",
	
	"chap-3/stating the problem.md",
	"styling/pagebreak.tex",
	
	"chap-3/stakeholders.md",
	"styling/pagebreak.tex",
	
	"chap-4/limitations.md",
	"styling/pagebreak.tex",
	
	"chap-4/existing_solutions.md",
	"styling/pagebreak.tex",
	
	"chap-4/research_questions.md",
	"styling/pagebreak.tex",
	
	"chap-4/feature_requirements.md",
	"styling/pagebreak.tex",
	
	"chap-4/success_criteria.md",
	"styling/pagebreak.tex",
	
	#"chap-4/approaches.md",
	#"styling/pagebreak.tex",
	
	"chap-4/software_requirements.md",
	"styling/pagebreak.tex",
);

my $DIR = "Analysis";

my $OUT_FILE = "$DIR.pdf";

my @EXTS = ("raw_tex", "grid_tables");

my $FONT_SIZE = "12pt";

my $CONTENTS_PAGE = 1;

my $CODE_STYLE = "tango";


sub main{	
	@ORDER = map { "'$_'" } @ORDER;

	my $md_files = join " 'styling/border.md' ", @ORDER;

	my $exts =  join "", (map { "+$_" } @EXTS);

	my $command = "echo '\n# $DIR\n' > ../build/$DIR.md && awk 'FNR==1 && NR!=1 {print \"\\n\"}{print}' $md_files| perl ../preprop.pl | sed 's/^#/##/g' | sed 's/images/$DIR\\/images/g' | cat >> ../build/$DIR.md";
	
	print "$command\n";

	`$command`;
}


&main;

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
	
	"chap-4/success_criteria.md",
	"styling/pagebreak.tex",
	
	"chap-4/feature_requirements.md",
	"styling/pagebreak.tex",
	
	#"chap-4/approaches.md",
	#"styling/pagebreak.tex",
	
	"chap-4/software_requirements.md",
	"styling/pagebreak.tex",
);

my $OUT_FILE = "Analysis.pdf";

my @EXTS = ("raw_tex", "grid_tables");

my $FONT_SIZE = "12pt";

my $CONTENTS_PAGE = 1;

my $CODE_STYLE = "tango";


sub main{	
	@ORDER = map { "'$_'" } @ORDER;

	my $md_files = join " 'styling/border.md' ", @ORDER;

	my $exts =  join "", (map { "+$_" } @EXTS);

	my $command = "pandoc $md_files meta.yaml -s --quiet -f markdown$exts --highlight-style=$CODE_STYLE -B before.tex --toc --toc-depth=1 -o '${OUT_FILE}' -t latex";
	
	print "$command\n";

	`$command`;
	
	`mv $OUT_FILE ../build`;
}


&main;

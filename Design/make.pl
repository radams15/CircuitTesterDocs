#!/usr/bin/perl
use strict;
use warnings;

my @MD_ORDER = (
	"styling/style.md",
	
	"styling/pagebreak.tex",
	
	"docs/decomposition.md",
	
	"styling/pagebreak.tex",
	
	"docs/design.md",
	
	"styling/pagebreak.tex",
	
	"docs/algorithms.md",
);

my @DIA_ORDER = <diagrams/*.dia>;

my $OUT_FILE = "Design.pdf";

my @EXTS = ("raw_tex", "grid_tables", "fenced_code_blocks", "backtick_code_blocks");

my $CONTENTS_PAGE = 1;

my $CODE_STYLE = "tango";


sub make_diagrams{
	foreach my $file (@DIA_ORDER){
		my $basename = $file;
		$basename =~ s{^.*/|\.[^.]+$}{}g;
		my $command = "dia '$file' -e 'images/$basename.png' -n";
		print "$command\n";
		`$command`;
	}
}

sub main{
	&make_diagrams;

	@MD_ORDER = map { "'$_'" } @MD_ORDER;

	my $md_files = join " 'styling/border.md' ", @MD_ORDER;

	my $exts =  join "", (map { "+$_" } @EXTS);

	my $command = "awk 'FNR==1 && NR!=1 {print \"\\n\"}{print}' $md_files meta.yaml| ../preprop.pl | pandoc -s --quiet -f markdown$exts --highlight-style=$CODE_STYLE -B before.tex  --toc --toc-depth=1 -o '${OUT_FILE}' -t latex";
	
	print "$command\n";

	`$command`;
	
	`mv $OUT_FILE ../build`;
}


&main;

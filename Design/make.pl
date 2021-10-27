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
	"docs/libraries.md",
	
	"styling/pagebreak.tex",
	"docs/algorithms.md",
	
	"styling/pagebreak.tex",
	"docs/validation.md",

	"styling/pagebreak.tex",
	"docs/test_plans.md",

	"styling/pagebreak.tex",
	"docs/future_steps.md",
	
	"styling/pagebreak.tex",
	"docs/sources.md",
);

my @DIA_ORDER = <diagrams/*.dia>;

my $DIR = "Design";

my $OUT_FILE = "$DIR.pdf";

my @EXTS = ("raw_tex", "grid_tables", "fenced_code_blocks", "backtick_code_blocks");

my $CODE_STYLE = "tango.theme";


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
	if(!($ARGV[0] eq "nod")){
		&make_diagrams;
	}

	@MD_ORDER = map { "'$_'" } @MD_ORDER;

	my $md_files = join " 'styling/border.md' ", @MD_ORDER;

	my $exts =  join "", (map { "+$_" } @EXTS);

	my $command = "echo '\n# $DIR\n' > ../build/$DIR.md && awk 'FNR==1 && NR!=1 {print \"\\n\"}{print}' $md_files| perl ../preprop.pl | sed 's/^#/##/g' | sed 's/images/$DIR\\/images/g' | cat >> ../build/$DIR.md";
	
	print "$command\n";

	print `$command`;
}


&main;

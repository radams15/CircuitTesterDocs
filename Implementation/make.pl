#!/usr/bin/perl
use strict;
use warnings;

my @MD_ORDER = (
	"styling/style.md",

	"styling/pagebreak.tex",
	"docs/intro.md",
	
	"styling/pagebreak.tex",
	"docs/stage1.md",

	"styling/pagebreak.tex",
	"docs/stage2.md",

	"styling/pagebreak.tex",
	"docs/stage3.md",
	
	"styling/pagebreak.tex",
	"docs/stage4.md",
	
	"styling/pagebreak.tex",
	"docs/stage5.md",
	
	"styling/pagebreak.tex",
	"docs/stage6.md",
	
	"styling/pagebreak.tex",
	"docs/stage7.md",
);


my $DIR = "Implementation";

my $OUT_FILE = "$DIR.pdf";

my @EXTS = ("raw_tex", "grid_tables", "fenced_code_blocks", "backtick_code_blocks");

my $CODE_STYLE = "tango.theme";

my @DIA_ORDER = <diagrams/*.dia>;

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

	my $command = "echo '\n# $DIR\n' > ../build/$DIR.md && awk 'FNR==1 && NR!=1 {print \"\\n\"}{print}' $md_files| perl ../preprop.pl | sed 's/^#/##/g' | sed 's/images/$DIR\\/images/g' | cat >> ../build/$DIR.md";
	
	print "$command\n";

	`$command`;
	
	`rm -rf code`;
}

&main;

#!/usr/bin/perl
use strict;
use warnings;

use File::Find;


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

	"styling/pagebreak.tex",
	"docs/final_code.md",
);


my $DIR = "Implementation";

my $OUT_FILE = "$DIR.pdf";

my @EXTS = ("raw_tex", "grid_tables", "fenced_code_blocks", "backtick_code_blocks");

my $CODE_STYLE = "tango.theme";

sub get_spice3{
	open(FH, ">", "docs/spice3.md");

	print FH "## Code\n\n\n";
	
	find( { wanted => sub {
		my $f = $_;
		if($f =~ /.*\.(py)/g){
			my $title = $f;
			#$title =~ s/code\/CircuitTester-master\/src\/(test|main)\///g;

			my $inc = "\n### $title\n\n\%include_cpp($f)";
			print FH "$inc\n";
		}
	}, no_chdir => 1 }, "spice3/" );

	close(FH);
}

sub get_code{
	`rm -rf code`;
	`wget 'https://github.com/radams15/CircuitTester/archive/refs/heads/master.zip'`;
	`unzip master.zip */src/* -d code`;
	`rm -rf master.zip`;

	open(FH, ">", "docs/final_code.md");

	print FH "# Full Source Code\n\n\n";
	
	find( { wanted => sub {
		my $f = $_;
		if($f =~ /.*\.(cc|h)/g){
			my $title = $f;
			$title =~ s/code\/CircuitTester-master\/src\/(test|main)\///g;

			my $inc = "\n## $title\n\n\%include_cpp($f)";
			print FH "$inc\n";
		}
	}, no_chdir => 1 }, "code/" );

	close(FH);
}


sub main{
	get_code();

	@MD_ORDER = map { "'$_'" } @MD_ORDER;

	my $md_files = join " 'styling/border.md' ", @MD_ORDER;

	my $exts =  join "", (map { "+$_" } @EXTS);

	my $command = "echo '\n# $DIR\n' > ../build/$DIR.md && awk 'FNR==1 && NR!=1 {print \"\\n\"}{print}' $md_files| perl ../preprop.pl | sed 's/^#/##/g' | sed 's/images/$DIR\\/images/g' | cat >> ../build/$DIR.md";
	
	print "$command\n";

	`$command`;
	
	`rm -rf code`;
}

&main;

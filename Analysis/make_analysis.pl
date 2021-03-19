#!/usr/bin/perl
use strict;
use warnings;

my @ORDER = ("chap-3/stating the problem.md", "chap-4/analysis.md");
my $OUT_FILE = "analysis.html";

my $CSS_FILE = "styling/style.css";

sub main{
	@ORDER = map { "'$_'" } @ORDER;

	my $md_files = join(" 'styling/border.md' ", @ORDER);

	my $command = "pandoc -s $md_files --quiet -f markdown -t html5 --css '${CSS_FILE}' -o '${OUT_FILE}'";

	#print "$command\n";
	`$command`;
}


&main;

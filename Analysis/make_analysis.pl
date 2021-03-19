use strict;
use warnings;

my @ORDER = ("stating the problem.md", "analysis.md");

my $OUT_FILE = "analysis.html";

sub main{
	@ORDER = map { "'$_'" } @ORDER;

	my $md_files = join(" ", @ORDER);

	my $command = "pandoc $md_files > '${OUT_FILE}'";

	print "$command\n";
	`$command`;
}


&main;

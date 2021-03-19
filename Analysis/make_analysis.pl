use strict;
use warnings;

use constant ORDER => ("stating the problem.md", "analysis.md");

use constant OUT_FILE => "analysis.pdf";

sub main{
	my $md_files = join(" ", ORDER);

	my $command = "pandoc $md_files > ${\OUT_FILE}";

	print "$command\n";
	`$command`;
}


&main;

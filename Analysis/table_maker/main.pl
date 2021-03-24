use strict;
use warnings;

use Data::Dumper;

sub read_file{
	my ($file) = @_;

	open(FH, '<', $file) or die $!;

	my $out = "";

	while(<FH>){
		$out .= $_;
	}

	close(FH);

	return $out;
}

sub convert{
	my ($data) = @_;

	my $out = "";

	my @rows = split "---", $data; # split up rows by "---"

	my $num_cols = undef;

	my $i = 0;
	foreach my $row (@rows){
		my $out_row = "";

		my @cols = split "%%", $row; # split up each row by %%

		if($i == 0){
			$num_cols = scalar @cols; # get col array length for only header
			if($num_cols < 1){
				die "No cols!\n";
			}
		}


		print ("+---+" x $num_cols), "\n";

		foreach my $col (@cols){
			chomp $col;
			print "| $col |";
		}
		print "|\n";

		$i++;
	}
	print ("+---+" x $num_cols), "\n";

	print "\n";
}

my $out = convert(read_file("in.txt"));

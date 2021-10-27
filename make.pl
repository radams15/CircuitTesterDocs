#!/usr/bin/perl

use strict;
use warnings;

use Cwd qw(getcwd);

my @FOLDERS = (
	"Analysis",
	"Design",
	"Implementation",
	"Evaluation",
);

my @MD_ORDER = (
	"global/meta.yaml",
	
	"global/pagebreak.tex",
	"build/Analysis.md",
	
	"global/pagebreak.tex",
	"build/Design.md",
	
	"global/pagebreak.tex",
	"build/Implementation.md",
	
	"global/pagebreak.tex",
	"build/Evaluation.md",
);


my @EXTS = ("raw_tex", "grid_tables", "fenced_code_blocks", "backtick_code_blocks");

my $BUILD_FOLDER = "build";

my $CODE_STYLE = "global/tango.theme";

sub file_write{
    my ($name, $data) = @_;

    open(FH, ">", $name) or die $!;

    print FH $data;

    close(FH);
}

my $OUT_FILE = "";

sub main{	
	my $before = getcwd;

	mkdir $BUILD_FOLDER;

	foreach my $folder (@FOLDERS){
		chdir $folder;

		print "$folder\n";

		my $command = "perl make.pl";
		`$command`;

		chdir $before;
	}
	
	my $exts =  join "", (map { "+$_" } @EXTS);
	
	my $md_files = join " ", @MD_ORDER;
	
	my $command = "awk 'FNR==1 && NR!=1 {print \"\\n\"}{print}' $md_files | pandoc -s -f markdown-implicit_figures$exts --highlight-style=$CODE_STYLE -B global/before.tex --listings -H global/header.tex --toc --toc-depth=2 -o '$BUILD_FOLDER/CircuitTester.pdf' -t latex --pdf-engine=xelatex && awk 'FNR==1 && NR!=1 {print \"\\n\"}{print}' $md_files | pandoc -s -f markdown-implicit_figures$exts --highlight-style=$CODE_STYLE -B global/before.tex --listings -H global/header.tex --toc --toc-depth=2 -o '$BUILD_FOLDER/CircuitTester.docx'";

	print "$command\n";
	
	print `$command`;

	print "Word Counts\n";
	
	my $wordcount_data = "<h1>Word Counts:</h1>\n";
	foreach my $file (<$BUILD_FOLDER/*.pdf>){		
		my $command = "pdftotext $file - | wc -w";
		
		my $num_words = `$command`;
		chomp $num_words;
		
		$wordcount_data .= "<h2>$file</h2><br><p>$num_words<p><br><br>";
	}
	
	file_write("$BUILD_FOLDER/wordcounts.html", $wordcount_data);
	
	`rm $BUILD_FOLDER/*.md`;
}

&main;

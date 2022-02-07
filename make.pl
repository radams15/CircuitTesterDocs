#!/usr/bin/perl

use strict;
use warnings;

use Cwd qw(getcwd);
use File::Find;

my @FOLDERS = (
	"Analysis",
	"Design",
	"Implementation",
	"Evaluation",
	"Bibliography",
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
	
	"global/pagebreak.tex",
	"build/Bibliography.md",

	"global/pagebreak.tex",
	"build/final_code.md",
);


my @EXTS = ("raw_tex", "grid_tables", "fenced_code_blocks", "backtick_code_blocks");

my $BUILD_FOLDER = "build";

my $CODE_STYLE = "global/tango.theme";

sub get_code{
	`rm -rf $BUILD_FOLDER/code`;
	`wget 'https://github.com/radams15/CircuitTester/archive/refs/heads/master.zip'`;
	`unzip master.zip */src/* -d $BUILD_FOLDER/code`;
	`rm -rf master.zip`;

	open(FH, ">", "build/final_code.md");

	print FH "# Appendix I: Full Source Code\n\n\n";
	
	find( { wanted => sub {
		my $f = $_;
		if($f =~ /.*\.h/g){
			my $title = $f;
			$title =~ s/$BUILD_FOLDER\/code\/CircuitTester-master\/src\/(test|main)\///g;
			my $f1 = $f;
			$f1 =~ s/build\///g;

			if($f1 eq "Saves/json.h"){
				next;
			}

			my $data = `cat $f | perl preprop.pl`;

			my $inc = "\n## $title\n\n```cpp\n\n$data\n\n```";
			print FH "$inc\n";
		}
	}, no_chdir => 1 }, "build/code/" );

	find( { wanted => sub {
		my $f = $_;
		if($f =~ /.*\.cc/g){
			my $title = $f;
			$title =~ s/$BUILD_FOLDER\/code\/CircuitTester-master\/src\/(test|main)\///g;
			my $f1 = $f;
			$f1 =~ s/build\///g;

			my $data = `cat $f | perl preprop.pl`;

			my $inc = "\n## $title\n\n```cpp\n\n$data\n\n```";
			print FH "$inc\n";
		}
	}, no_chdir => 1 }, "build/code/" );

	close(FH);
}

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

	get_code();

	foreach my $folder (@FOLDERS){
		chdir $folder;

		print "$folder\n";

		my $command = "perl make.pl";
		`$command`;

		chdir $before;
	}
	
	my $exts =  join "", (map { "+$_" } @EXTS);
	
	my $md_files = join " ", @MD_ORDER;
	
	my $command = "awk 'FNR==1 && NR!=1 {print \"\\n\"}{print}' $md_files | pandoc -s -f markdown-implicit_figures$exts --highlight-style=$CODE_STYLE -B global/before.tex --listings -H global/header.tex --toc --toc-depth=3 -o '$BUILD_FOLDER/CircuitTester.pdf' -t latex --pdf-engine=xelatex && awk 'FNR==1 && NR!=1 {print \"\\n\"}{print}' $md_files | pandoc -s -f markdown-implicit_figures$exts --highlight-style=$CODE_STYLE -B global/before.tex --listings -H global/header.tex --toc --toc-depth=2 -o '$BUILD_FOLDER/CircuitTester.docx'";

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

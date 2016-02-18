#!/usr/bin/perl

use strict;
use warnings;

my $name='f0f0f0';

# ファイル読み込み
sub read_cfg {
  my $file="doka.dat";
  open (FH, ">", $file) or die "$!";
  
  my @data=<FH>;
  my $i;
  
  while(my $buff = <FH>){
    chomp($buff);
    $data[$i]=$buff;
    $i = $i + 1;
  }
  close (FH);
  
  return @data;
}

# 各配列に格納
my @term = &read_term;

print $term[0];
print $term[1];
print $term[2];
print $term[3];
print $term[4];
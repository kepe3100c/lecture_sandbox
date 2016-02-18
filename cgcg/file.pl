#!/usr/bin/perl

use strict;
use warnings;

# ポイントファイル読み込み
sub read_point {
  my $file="gg.dat";
  open (IN, $file) or die "$!";
  my @data = split(/,/, <IN>);

  close (IN);
  
  return @data;
}

# 各配列に格納W
my @point = &read_point;

# 
sub read_point2 {
  my $i;
  my @file_list = glob "aa*";
  my @data;
  
  for($i = 0; $i < @file_list; $i++)
  {
    open (IN, $file_list[$i]) or die "$!";
    @data[$i] = split(/,/, <IN>);
    close (IN);
  }

  print $data[1] . "\n";
  
  return @data;
}

my @popo = &read_point2;

print $popo[0] . "\n";
#!/usr/bin/perl

use strict;
use warnings;

# 設定ファイル読み込み
sub read_term {
  my $file="zz.dat";
  open (IN, $file) or die "$!";
  my @data = split(/,/, <IN>);

  close (IN);
  
  return @data;
}

# ポイントファイル読み込み
sub read_point {
  my $file="gg.dat";
  open (IN, $file) or die "$!";
  my @data = split(/,/, <IN>);

  close (IN);
  
  return @data;
}

# 各配列に格納
my @term = &read_term;
my @point = &read_point;

# 試験的にプリント
# print $term[1] . "\n";

if(length($point[13]) == 0)
{
  # print "goha" . "\n";
}

sub oha {
  my @hoa = (1,2);
  my $hu;
  
  if($_[0] == 0)
  {
    $hu = $hoa[0];
  }else{
    $hu = $hoa[1];
  }
  
  return $hu;
}

my $ghu = &oha(1);

print $ghu . "\n";
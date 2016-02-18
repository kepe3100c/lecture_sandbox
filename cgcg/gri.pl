#!/usr/bin/perl

use strict;
use warnings;

my $fro='CURRENT_FPNUMBER=';
my $fpnum = 'f0f0f0';

# ファイル読み込み
sub read_cfg {
  my $file="terminal.cfg";
  open (FH, $file) or die "$!";
  
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

# 書き込み
sub write_cfg {
  # 引数で渡されたものを格納
  my @arr=@_;
  my $file="terminal.cfg";
  open (FH, ">", $file) or die "$!";
  
  print FH "$arr[0]$arr[1]$arr[2]$arr[3]CURRENT_FPNUMBER=$arr[5]\n";
  
  close (FH);
}

# 読み込んだデータを格納
my @term = &read_cfg;

# 書き込み実行
&write_cfg(@term,$fpnum);

print @term;
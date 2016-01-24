use strict;
use warnings;

# 引数の処理
my $file = "zz.dat";

unless ($file) {
  # 引数がないときは、使用方法を示して終了。
  die "Usage: $0 file"; 
}

# ファイルを解析してcsv形式のデータを配列の配列に変換。
my @recs = parse_file($file);

# 出力( 2次元配列なので、forでたどる )
for my $items (@recs) {
  # カンマで連結して出力。
  print join(',', @$items) . "\n";
}

# ファイル解析用の関数( 今回は単に書き戻すだけだけれど・・ )
sub parse_file {
  my $file = shift;
    
  open(my $fh, "<", $file)
    or die "Cannot open $file for read: $!";
  
  # 複数のレコードを格納する配列へのリファレンスを準備
  my $recs = []; 
  while (my $line = <$fh>) {
    chomp $line; # 改行を取り除く
    
    # データを格納する配列へのリファレンスを準備
    # カンマで行を分けて配列に格納
    # splitは配列を返すので、
    # @$itemsでデリファレンス

    my $items = []; 
    @$items = split(/,/, $line); 

    # push関数の第1引数は配列なので、@$recs
    # とデリファレンス。
    push @$recs, $items;
  }
  close $fh;    
  return $recs; 
}
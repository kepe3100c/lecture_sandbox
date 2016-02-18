#!/bin/sh

TARGET=$1

# pid調査用
grep_func () {
  ps | grep -w ${TARGET} | grep -v grep | grep -w -e -R | awk '{ print $2; }'
}

# 検出されたpidのkill関数
kill_func () {
  # pidsに該当プロセスpidを格納
  pids=`grep_func`
  # kill実行
  for pid in ${pids[*]}
  do
  kill -9 ${pid}
  done
  # 再格納
  pids=`grep_func`
  # プロセスがkillしきれなかった場合再帰
  if [ $pids > 0 ]; then
    kill_func
  fi
}

# 実行
kill_func

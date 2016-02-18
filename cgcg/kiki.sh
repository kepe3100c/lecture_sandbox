#!/bin/sh

# USER=ubuntu
TARGET=vim
hantei=2

pids=`ps -ef | grep ${TARGET} | grep -v grep | grep -w -e -R | awk '{ print $2; }'`

grep_func () {
  `ps -ef | grep ${TARGET} | grep -v grep | grep -w -e -R | awk '{ print $2; }'`
}

kill_func () {
  for pid in ${pids[*]}
  do
  kill -9 ${pid}
  done
  hantei=1
  
  grep_func
  if [ $? > 0 ]; then
    kill_func
  fi
}

kill_func

while [ $hantei = 100 ]
do
  #echo "AA"
  #po=grep_func
  
  if [ $po != 0 ]; then
    # $hantei=2
    :
      
  fi
  
  #kill_func
done


#for pid in ${pids[*]}
#do
#  kill -9 ${pid}
#  echo "GOHA"
#done

#!/bin/bash

API="http://www.google.com/speech-api/v1/recognize?lang=en"

echo " === START ==="

JSON=`arecord -f cd -t wav -d 3 -r 16000 | flac - -f --best --sample-rate 16000 -o out.flac;\
wget -O - -o /dev/null --post-file out.flac --header="Content-Type: audio/x-flac; rate=16000" "$API"`

echo "JSON is $JSON"
echo "=== JSON FINISHED ==="

UTTERANCE=`echo $JSON\
 |sed -e 's/[{}]/''/g'\
  |awk -v k="text" '{n=split($0,a,","); for (i=1; i<=n; i++) print a[i]; exit }'\
   |awk -F: 'NR==3 { print $3; exit }'\
    |sed -e 's/["]/''/g'`
echo "utterance: $UTTERANCE"

CMD_MUSIC_START="start music"
CMD_MUSIC_STOP="stop music"
CMD_NEXT_SONG="next song"
CMD_PREV_SONG="previous song"
CMD_PAUSE_SONG="stop song"

command=0

if [ `echo "$UTTERANCE" | grep -ic "^$CMD_MUSIC_START$"` -gt 0 ]; then
	command=1
elif [ `echo "$UTTERANCE" | grep -ic "^$CMD_MUSIC_STOP$"` -gt 0 ]; then
	command=2
elif [ `echo "$UTTERANCE" | grep -ic "^$CMD_NEXT_SONG$"` -gt 0 ]; then
	command=3
elif [ `echo "$UTTERANCE" | grep -ic "^$CMD_PREV_SONG$"` -gt 0 ]; then
	command=4
elif [ `echo "$UTTERANCE" | grep -ic "^$CMD_PAUSE_SONG$"` -gt 0 ]; then
	command=5
fi

rm out.flac

echo "command $command"
echo "***UTTERANCE*** $UTTERANCE"

exit $command

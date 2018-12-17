#!/bin/bash

longueur=(4 5 6 7 8 9 10 15 20 30 40 50)
alphabet=(2 4 20 70)
text_size=500000

mkdir -p ../words

for i in "${alphabet[@]}"
do
  rm -f ../words/generated_words_$i.txt
  rm -f ../words/generated_text_$i.txt
done

for i in "${alphabet[@]}"
do

  ./gen_texte text_output.txt $text_size $i
  cat text_output.txt > ../words/generated_text_$i.txt

  for j in "${longueur[@]}"
  do
    ./gen_mots word_output.txt 100 $j $i
    cat word_output.txt > ../words/generated_words_$i.txt
  done
done

rm text_output.txt
rm word_output.txt

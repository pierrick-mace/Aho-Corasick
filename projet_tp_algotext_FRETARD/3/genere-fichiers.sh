#!/bin/bash

case "$1" in
  clean)
        files=`ls | grep 'txt[0-9]*.txt\|w[0-9]*.l[0-9]*-[0-9]*.txt'`
        for f in $files
        do
            echo "rm $f"
            rm $f
        done
        ;;
  *)
        textLength=5000000
        textAlphabets="2 4 20 70"
        nbOfWords=100
        wordMinLength=5
        wordLengths="15 30 60"

        for alph in $textAlphabets
        do
            minLength=$wordMinLength
            generate="./genere-texte $textLength $alph > txt$alph.txt"
            echo $generate
            eval $generate
            for maxLen in $wordLengths
            do
                generate="./genere-mots $nbOfWords $minLength $maxLen $alph"
                generate+=" > w$alph.l$minLength-$maxLen.txt"
                echo $generate
                eval $generate
                minLength=$maxLen
            done
        done
        ;;
esac

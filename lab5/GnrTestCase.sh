#!/usr/bin/env bash

for text in "Hello World" "Hello Worl" "Hello Word" "Hello Wold" "Hello orld" "Hell World" "Helo World" "Hllo World" "ello World";
do
	echo "\"$text\"", \"`md5sum <<< $text`\"
done


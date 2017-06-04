#!/bin/bash

if(($# != 1)); then
	echo "error: path to CppCoreGuidelines.md is required"
	exit 1
fi

if ! [[ $(basename $1) == "CppCoreGuidelines.md" ]]; then
	echo "error: path to CppCoreGuidelines.md is required"
	exit 1
fi

if ! [[ -f "$1" ]]; then
	echo "error: file $1 does not exist"
	exit 1
fi

DIR=$(dirname $1)
SOURCE=${DIR}/contrib
SECTIONS=${DIR}/sections

echo "DIR: $DIR"
echo "SOURCE: $SOURCE"
echo "SECTIONS: $SECTIONS"

make -C ${SOURCE}

git rm --ignore-unmatch "${SECTIONS}/*.md"
${SOURCE}/extract-sections -c -d -s -i "$1" "${SECTIONS}"
git add "${SECTIONS}/*.md"
git commit -m "update-sections.sh" "${SECTIONS}/*.md"

#echo rm -f ${SECIONS}/*.md && make && ./extract-sections ../CppCoreGuidelines.md ../sections -c -d -s -i

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
	echo "error: filr $1 does not exist"
	exit 1
fi

PATH=${1%%CppCoreGuidelines.md}
SOURCE=${PATH}/contrib
SECTIONS=${PATH}/sections

echo "PATH: $PATH"
echo "SOURCE: $SOURCE"
echo "SECTIONS: $SECTIONS"

cd ${SOURCE}
make
cd -

echo git rm "${SECTIONS}/*.md"
echo ${SOURCE}/extract-sections -c -d -s -i "$1" "${SECTIONS}"
echo git add "${SECTIONS}/*.md"
echo git commit -m "update-sections.sh" "${SECTIONS}/*.md"

#rm -f ../sections/*.md && make && ./extract-sections ../CppCoreGuidelines.md ../sections -c -d -s -i

#!/bin/bash

#rm "$(ls --ignore '*.cpp' --ignore '*.md' --ignore '*.sh')"
rm -rf `ls | grep -v "cpp$\|md$\|sh$"`

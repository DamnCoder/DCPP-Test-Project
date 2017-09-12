#!/bin/sh

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

cd ${DIR}
cd ..

FILE_OUTPUT="./project"
TEMPLATES_PATH="./utilities/NewClassProject/Templates"

mono ./utilities/NewClassProject/NewClass/bin/Debug/NewClass.exe $TEMPLATES_PATH $FILE_OUTPUT materialmanager DCPP "Jorge López González" TMaterialManager dc material header_only
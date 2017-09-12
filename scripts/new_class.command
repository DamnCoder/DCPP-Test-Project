#!/bin/sh

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

cd ${DIR}
cd ..

FILE_OUTPUT="./project"
TEMPLATES_PATH="./utilities/NewClassProject/Templates"

FILE_NAME="logictest"
PROJECT_NAME="DCPPTest"
AUTHOR="Jorge López González"
CLASS_NAME="CLogicTest"
NAMESPACE="dc"
FOLDER="logic"

mono ./utilities/NewClassProject/NewClass/bin/Debug/NewClass.exe $TEMPLATES_PATH $FILE_OUTPUT $FILE_NAME $PROJECT_NAME "Jorge López González" $CLASS_NAME $NAMESPACE $FOLDER
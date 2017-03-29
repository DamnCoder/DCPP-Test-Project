#!/bin/sh

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR
# -H indicates where the project sources are located
# -B indicates where the build folder will be located
cmake -Hproject -Bbuild
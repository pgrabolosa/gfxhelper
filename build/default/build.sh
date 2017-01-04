#!/bin/bash

OSX=false
DEBUG=false
COMPILE_LIB=true
COMPILE_APP=true

######################################################
# Make sure the required environment is loaded on OS X

if [ `uname` == 'Darwin' ]; then
  OSX=true
  
  if [ -z "${JHBUILD_PREFIX}" ]; then
    echo "You must execute this command from the JHBUILD shell."
    echo "Please run '~/.local/bin/jhbuild shell' first."
    exit 1
  fi
fi

######################################################
# Check for options

args=`getopt d $*`
if [ $? != 0 ]; then
  echo 'Usage: [-d] [-L|l] [c files]'
  echo '  -d Enable debugging.'
  echo '  -l Do not compile the library.'
  echo '  -L Only compile the library.'
  exit 2
fi
set -- $args
for i
do
  case "$i" in
    -d)
      DEBUG=true
      shift;;
    -l)
      COMPILE_LIB=false
      shift;;
    -L)
      COMPILE_APP=false
      shift;;
    --)
      shift; break;;
  esac
done

######################################################
# Get the proper paths

pushd . > /dev/null
SCRIPT_PATH="${BASH_SOURCE[0]}";
while([ -h "${SCRIPT_PATH}" ]); do
  cd "`dirname "${SCRIPT_PATH}"`"
  SCRIPT_PATH="$(readlink "`basename "${SCRIPT_PATH}"`")";
done
cd "`dirname "${SCRIPT_PATH}"`" > /dev/null
SCRIPT_PATH="`pwd`";
popd  > /dev/null

pushd "${SCRIPT_PATH}/../.." > /dev/null
BASE_PATH="`pwd`"
OUTPUT_PATH="${BASE_PATH}/bin"
GFXSRC_PATH="${BASE_PATH}/src"
popd > /dev/null
mkdir -p "${OUTPUT_PATH}"

######################################################

if [ $COMPILE_LIB ]; then
  echo "Building GfxHelper library..."
  gcc -shared -std=c11 -I"${GFXSRC_PATH}" `pkg-config --cflags --libs gtk+-3.0` -o "${OUTPUT_PATH}/libGfxHelper.so" ${GFXSRC_PATH}/*.c
fi

if [ $COMPILE_APP ]; then
  echo "Building app..."
  gcc -std=c11 -L"${OUTPUT_PATH}" -lGfxHelper -I"${GFXSRC_PATH}" -o "${OUTPUT_PATH}/app.exe" $@
fi

echo "Done."
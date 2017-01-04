#!/bin/bash

CC_FLAGS=" -std=c11 "

OSX=false
DEBUG=false
COMPILE_LIB=true
COMPILE_APP=true
COMPILE_BUNDLE=true

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

args=`getopt bald $*`
if [ $? != 0 ]; then
  echo 'Usage: [-bald] [c files]'
  echo '  -b Do not compile the bundle (Mac only).'
  echo '  -a Do not compile the app.'
  echo '  -l Do not compile the library.'
  echo '  -d Enable debugging.'
  exit 2
fi
set -- $args
for i
do
  case "$i" in
    -d)
      DEBUG=true
      CC_FLAGS="${CC_FLAGS} -g "
      shift;;
    -l)
      COMPILE_LIB=false
      shift;;
    -a)
      COMPILE_APP=false
      shift;;
    -b)
      COMPILE_BUNDLE=false
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

if [ $COMPILE_LIB == true ]; then
  echo "Building GfxHelper library..."
  gcc $CC_FLAGS -shared -I"${GFXSRC_PATH}" `pkg-config --cflags --libs gtk+-3.0` -o "${OUTPUT_PATH}/libGfxHelper.so" ${GFXSRC_PATH}/*.c
  if [ $? != 0 ]; then
    echo "ERROR: Compiling the library failed."
    exit $?
  fi
  
  echo "Done."
fi

if [ $COMPILE_APP == true ]; then
  echo "Building app..."
  gcc $CC_FLAGS -L"${OUTPUT_PATH}" -lGfxHelper -I"${GFXSRC_PATH}" -o "${OUTPUT_PATH}/app.exe" $@
  if [ $? != 0 ]; then
    echo "ERROR: Compiling the app failed."
    exit $?
  fi

  echo "Done."
  
  if [ $DEBUG == true ]; then
    echo "Debug using:"
    echo "   gdb -ex run '${OUTPUT_PATH}/app.exe'"
    echo "   llvm -o run '${OUTPUT_PATH}/app.exe'"
  fi
fi

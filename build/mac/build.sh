#!/bin/bash

########################################
# Clean script path
pushd . > /dev/null
MAC_SCRIPT_PATH="${BASH_SOURCE[0]}";
while([ -h "${MAC_SCRIPT_PATH}" ]); do
  cd "`dirname "${MAC_SCRIPT_PATH}"`"
  MAC_SCRIPT_PATH="$(readlink "`basename "${MAC_SCRIPT_PATH}"`")";
done
cd "`dirname "${MAC_SCRIPT_PATH}"`" > /dev/null
MAC_SCRIPT_PATH="`pwd`";
popd  > /dev/null

########################################
# Run the build script
source "${MAC_SCRIPT_PATH}/../default/build.sh"

########################################
# Build a bundle app
if [ $COMPILE_BUNDLE == true ]; then
  echo "Building the Mac bundle..."
  rm -rf "${MAC_SCRIPT_PATH}/bundle/GtkDemo.app"
  gtk-mac-bundler "${MAC_SCRIPT_PATH}/bundle/myapp.bundle" 2>&1 >/dev/null
  if [ $? != 0 ]; then
    echo "ERROR: gtk-mac-bundler failed."
    exit $?
  fi
  
  mv -f "${MAC_SCRIPT_PATH}/bundle/GtkDemo.app" "${OUTPUT_PATH}/"
  echo "Done."
fi

# Copy the binaries where needed
cp -f "${OUTPUT_PATH}/app.exe" "${OUTPUT_PATH}/GtkDemo.app/Contents/MacOS/GtkDemo-bin"
cp -f "${OUTPUT_PATH}/libGfxHelper.so" "${OUTPUT_PATH}/GtkDemo.app/Contents/Resources/lib/"
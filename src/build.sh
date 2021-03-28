#!/bin/bash
cd `dirname $0`
rm -rf build
mkdir -p build
qmake ./DDEDock-BasicPlugin.pro -spec linux-g++ CONFIG+=qtquickcompiler -o build/
cd build/
make
sudo cp `dirname $0`/libbasicplugin.so /usr/lib/dde-dock/plugins/libbasicplugin.so
killall dde-dock
cd ..
rm -rf build
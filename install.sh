#!/bin/bash
# use /usr/lib/dde-dock/plugins/system-trays to use as tray instead of system plugins part
sudo cp `dirname $0`/libbasicplugin.so /usr/lib/dde-dock/plugins/libbasicplugin.so
killall dde-dock

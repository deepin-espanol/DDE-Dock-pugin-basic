#!/bin/bash
sudo cp `dirname $0`/libbasicplugin.so /usr/lib/dde-dock/plugins/libbasicplugin.so
killall dde-dock
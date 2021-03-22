# DDE-Dock-pugin-basic
example of development of a plugin for dde-dock This project is a learning exercise of plugin development for the Qt and DDE Dock with the aim of implementing one of the Dock plugins

## Dependencies

On Debian, the following packages are required.
```
 - dde-dock-dev -> Interfaces for Deepin's dock plugins
 - qtbase5-dev  -> Qt Core and Qt Widgets
```
## Customization
In the file install.sh and uninstall.sh, there's the path ```/usr/lib/dde-dock/plugins```
This makes the dock use the plugin in the part of the system ones. It'll be shown near of the trahs, nor date time plugin. For your user's experience, the best could be to use anotherpathe:
```/usr/lib/dde-dock/plugins/system-trays```
It then should appear in the section where there's the WIFI for example.

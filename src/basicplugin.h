#ifndef DDE_BASICDOCKPLUGIN_H
#define DDE_BASICDOCKPLUGIN_H

#include "dde-dock/pluginsiteminterface.h"      // El archivo de cabecera de plugins DDE Dock

// Introduce el archivo de cabecera del interfaz de usuario. Generalmente separan la interfaz del Dock del plugin, cada una en una clase.
#include "mainplugin.h"          // Archivos de encabezamiento del Plugin
#include "basicpluginpopup.h"     // El archivo de encabezamiento de la ventana emergente del plug-in

#include <QLabel>
#include <QTimer>                   // Usar temporizadores para actualizar dinámicamente la interfaz de usuario del plugin
#include <qrandom.h>                // Se utiliza para generar números aleatorios

class BasicPluginPlugin : public QObject, PluginsItemInterface
{
    Q_OBJECT
    Q_INTERFACES(PluginsItemInterface)
    Q_PLUGIN_METADATA(IID "com.deepin.dock.PluginsItemInterface" FILE "basicDock.json")

public:
    explicit BasicPluginPlugin(QObject *parent = 0);      // constructor para inicializar el plugin

    const QString pluginName() const override;              // El nombre del plugin, que DDE utiliza como base para la gestión del plugin
    const QString pluginDisplayName() const override;       // Nombre en pantalla del plugin
    void init(PluginProxyInterface *proxyInter) override;   // Cómo inicializar el plugin

    void pluginStateSwitched() override;                        // Evento: Cambio de estado del plugin
    bool pluginIsAllowDisable() override { return true; }       // Devuelve si se permite cerrar el plugin, lo que generalmente es así.
    bool pluginIsDisable() override;                            // Vuelva si el plugin está desactivado

    int itemSortKey(const QString &itemKey);
    void setSortKey(const QString &itemKey, const int order);

    // Los tres métodos siguientes proporcionarán la correspondiente interfaz de usuario a dde-dock para su visualización.
    QWidget *itemWidget(const QString &itemKey) override;       // La UI del plugin
    QWidget *itemTipsWidget(const QString &itemKey) override;   // La UI del Plugin
    QWidget *itemPopupApplet(const QString &itemKey) override;  // La UI pop-up plug-in

    const QString itemCommand(const QString &itemKey) override; // Haga clic en el plug-in para ejecutar el comando de shell, generalmente no es necesario, devolver una cadena vacía puede ser
    const QString itemContextMenu(const QString &itemKey) override;     // Definir el menú contextual del plug-in (es decir, el menú del botón derecho del ratón)

    void invokedMenuItem(const QString &itemKey, const QString &menuId, const bool checked) override;   // Definir eventos para hacer clic en los elementos del menú del plugin, similar a OnClick en los widgets de Android.

private:
    QPointer<BasicPlugin> m_widgetMainUI;             // El puntero al plugin
    QPointer<QLabel> m_tipsLabel;                       // El puntero al cuerpo del plugin
    QPointer<BasicPluginPopup> m_widgetPopupUI;       // Apuntando al cuerpo del popup
    QSettings m_settings;                               // QSettings es el módulo de gestión de la configuración de la aplicación proporcionado por Qt.
    QTimer *m_refreshTimer;                             // Temporizador para refrescar el plugin UI

    QRandomGenerator *randomGen;                        // Generador de números aleatorios, usado durante las pruebas de UI

    // La acción que se realiza cuando se hace clic en el menú contextual. En ambos casos, se muestra una ventana (o cuadro de diálogo).
    void about();
    void helloWorld();

/* Uso de la función de ranura para actualizaciones de plugins */
private slots:
    void updateBasicDock();         // Actualizar la interfaz de usuario del plug-in

};

#endif // DDE_BASICDOCKPLUGIN_H

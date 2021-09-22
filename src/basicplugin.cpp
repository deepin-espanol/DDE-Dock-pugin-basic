#include "basicplugin.h"

#include <QLabel>
#include <QWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QApplication>


BasicPluginPlugin::BasicPluginPlugin(QObject *parent)
    : QObject(parent),
      // Las siguientes líneas son miembros de la clase de inicialización, no heredadas
      m_tipsLabel(new QLabel),                   // Iniciar la etiqueta de aviso
      m_settings("deepin", "DDEBasicPlugin"),      // Módulo de configuración de la inicialización
      m_refreshTimer(new QTimer(this)),          // Inicializando temporizador
      randomGen(new QRandomGenerator())          // Iniciando el generador de números aleatorios
{
    /* Definir el formato de la etiqueta */
    m_tipsLabel->setObjectName("basicdock");        // nombre del objeto
    m_tipsLabel->setStyleSheet("color:white; padding:0px 3px;");    // Usando CSS para establecer la apariencia

    /* Creando nuevas instancias del plugin */
    m_widgetMainUI = new BasicPlugin;

    /* Crear una nueva instancia del plugin popup */
    m_widgetPopupUI = new BasicPluginPopup;

    /* Configuración del emporizador */
    m_refreshTimer->setInterval(1000);          // Determinar el intervalo de actualización de la UI
    m_refreshTimer->start();                    // ajusta el temporizador

    /* Conexión de las señales */
    // Conectar la señal de tiempo del temporizador a la ranura de la función de actualización de la UI,
    // para que la UI se actualice automáticamente cuando el temporizador esté funcionando
    // Tengan en cuenta que el tercer parámetro - el contexto - tiene que ser configurado correctamente,
    // de lo contrario obtendrán un error de compilación y no podrán encontrar la clase donde se encuentra
    // la tragamonedas en el IntelliSense de Qt!
    connect(m_refreshTimer, &QTimer::timeout, this, &BasicPluginPlugin::updateBasicDock);
    connect(m_refreshTimer, &QTimer::timeout, m_widgetPopupUI, &BasicPluginPopup::updatePopupUI);
    // el plugin solicita una señal actualizada para conectarse al protocolo (proxy) de ddde-dock.
    // Pero en realidad, la interfaz de usuario del plugin puede ser actualizada como de costumbre sin esta conexión.
    //connect(m_widgetMainUI, &BasicPlugin::requestUpdateGeometry, [this] { m_proxyInter->itemUpdate(this, pluginName()); });
}

/* Poner el nombre del plugin */
const QString BasicPluginPlugin::pluginName() const
{
    return "BasicDock";
}

/* Configurar el nombre del plugin a mostrar en pantalla */
const QString BasicPluginPlugin::pluginDisplayName() const
{
    return tr("Basic Dock");
}

/* Inicialización del plugin */
void BasicPluginPlugin::init(PluginProxyInterface *proxyInter)
{
    // El siguiente código pone el plugin en la bandja del dock
    m_proxyInter = proxyInter;
    if (m_widgetMainUI->enabled())
        m_proxyInter->itemAdded(this, pluginName());
}

/* Cambiar el estado de carga del plugin */
void BasicPluginPlugin::pluginStateSwitched()
{
    m_widgetMainUI->setEnabled(!m_widgetMainUI->enabled());
    if (m_widgetMainUI->enabled())
        m_proxyInter->itemAdded(this, pluginName());
    else
        m_proxyInter->itemRemoved(this, pluginName());
}

/* Comprueba si el plugin está desactivado */
bool BasicPluginPlugin::pluginIsDisable()
{
    return !m_widgetMainUI->enabled();
}

/* Obtener la ubicación de clasificación de los enchufes */
// El valor de retorno de la función es el número de serie del lugar donde se espera que se coloque el plugin.
int BasicPluginPlugin::itemSortKey(const QString &itemKey)
{
    Q_UNUSED(itemKey);      // Estamos usando valores que se guardan en la configuración, así que no necesitamos el nombre de la clave (?) proporcionado por itemKey.

    const QString key = QString("pos_%1").arg(displayMode());
    return m_settings.value(key, 0).toInt();
}

/* Grabar la ubicación de clasificación del plug-in */
// Guarda la ubicación de clasificación del plugin en la configuración
void BasicPluginPlugin::setSortKey(const QString &itemKey, const int order)
{
    Q_UNUSED(itemKey);

    const QString key = QString("pos_%1").arg(displayMode());
    m_settings.setValue(key, order);
}

/* Volver al objeto del plugin */
QWidget *BasicPluginPlugin::itemWidget(const QString &itemKey)
{
    Q_UNUSED(itemKey);
    return m_widgetMainUI;
}

/* Vuelva al objeto de la pista */
QWidget *BasicPluginPlugin::itemTipsWidget(const QString &itemKey)
{
    Q_UNUSED(itemKey);
    return m_tipsLabel;
}

/* Devuelve el objeto emergente */
QWidget *BasicPluginPlugin::itemPopupApplet(const QString &itemKey)
{
    Q_UNUSED(itemKey);
    return m_widgetPopupUI;
}

/* Especifica el comando de shell que el plugin hace clic para ejecutar, normalmente va vacío. */
const QString BasicPluginPlugin::itemCommand(const QString &itemKey)
{
    Q_UNUSED(itemKey);
    return "";
}

/* Añadir un menú contextual para el plugin */
// -Cada elemento del menú en la QList es un par clave-valor del QMap.
// Las claves comúnmente utilizadas son: itemId→menu nombre del artículo, itemText→menu nombre de visualización del artículo, isActive→whether disponible.
// -Exportar menú: los elementos del menú se exportan eventualmente, primero encapsulados por un QMap.
// Las claves para encapsular el QMap son: items→menu item QList, checkableMenu→set sea una marca de verificación o no.
// singleCheck→Sets si el menú es de una sola opción o no.
// El resultado final exportado es QJsonDocument.
const QString BasicPluginPlugin::itemContextMenu(const QString &itemKey)
{
    Q_UNUSED(itemKey);

    // Definir una lista QL para almacenar los elementos del menú
    QList<QVariant> items;
    items.reserve(1);

    // Primer elemento del menú
    QMap<QString, QVariant> mnuAbout;
    mnuAbout["itemId"] = "about";
    mnuAbout["itemText"] = tr("Acerca de");
    mnuAbout["isActive"] = true;
    items.push_back(mnuAbout);

    // Segundo elemento del menú
    QMap<QString, QVariant> mnuHelloWorld;
    mnuHelloWorld["itemId"] = "helloworld";
    mnuHelloWorld["itemText"] = tr("Hola mundo");
    mnuHelloWorld["isActive"] = true;
    items.push_back(mnuHelloWorld);

    // Tercer elemento del menú
    QMap<QString, QVariant> mnuAboutQt;
    mnuAboutQt["itemId"] = "aboutqt";
    mnuAboutQt["itemText"] = tr("Acerca de qt");
    mnuAboutQt["isActive"] = true;
    items.push_back(mnuAboutQt);

    // Encapsular los elementos del menú
    QMap<QString, QVariant> menu;
    menu["items"] = items;
    menu["checkableMenu"] = false;
    menu["singleCheck"] = false;

    // Exporta los resultados. El resultado está en formato JSON.
    return QJsonDocument::fromVariant(menu).toJson();
}

/* Elemento del menú haga clic en eventos */
void BasicPluginPlugin::invokedMenuItem(const QString &itemKey, const QString &menuId, const bool checked)
{
    Q_UNUSED(itemKey);
    Q_UNUSED(checked);

    // Determinar qué elemento del menú se pulsó en base al valor pasado por menuId.
    // Nota: No puedes usar switch, porque el switch sólo admite números enteros.
    if(menuId == "about") {
        about();
    }
    else if(menuId == "helloworld") {
        helloWorld();
    }
    else if(menuId == "aboutqt") {
        qApp->aboutQt();
    }
}


/** La siguiente parte es su propio código **/

/* Mostrar un cuadro de diálogo "Acerca de". */
void BasicPluginPlugin::about()
{
    QMessageBox aboutMB(QMessageBox::NoIcon, "Plugin básico para el dock",
                        "aquí hay un ejemplo simple de un desarrollo de un plugin de dde-dock! \n Autor: Deepin en español");
    aboutMB.setIconPixmap(QPixmap(":/icons/Logo-Racoon.png"));
    aboutMB.exec();
}

/* Mostrar un cuadro de diálogo de Hola Mundo. */
void BasicPluginPlugin::helloWorld()
{
    QMessageBox helloWorldMB(QMessageBox::Information, "Hola Mundo!", "Hola, Deepin. DDE Dock！");
    helloWorldMB.exec();
}

/* Recargando la interfaz de usuario */
// Este plug-in demostrará:
// -Display números aleatorios en el cuerpo del plug-in.
// -Mostrar otro número al azar en el indicador del plug-in.
void BasicPluginPlugin::updateBasicDock()
{
    m_widgetMainUI->setText(QString::number(randomGen->generate()));
    m_widgetMainUI->update();
    m_tipsLabel->setText("¡Los números aleatorios se generan usando el QRandomGenerator! \n Número actual al azar." + QString::number(randomGen->generate()));
}


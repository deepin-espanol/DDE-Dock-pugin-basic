#include "mainplugin.h"
//#include "dde-dock/constants.h"
#include <QApplication>
#include <QPainter>

#define PLUGIN_STATE_KEY "enable"

/* Aquí inician algunos datos básicos para la interfaz del plug-in. */
BasicPlugin::BasicPlugin(QWidget *parent)
    : QWidget(parent),
      m_settings("deepin", "DDEBasicPlugin")      // Iniciar el almacenamiento de la configuración del plugin
{
    text = "Por favor espera...";
}

/* Ver la disponibilidad de los plugins */
// Este método será llamado por la interfaz del Dock para determinar si mostrar el plugin en el Dock determinando el valor aquí
bool BasicPlugin::enabled()
{
    // El estado disponible del plug-in se almacena en los ajustes, donde se lee de la siguiente manera
    return m_settings.value(PLUGIN_STATE_KEY, true).toBool();
}

/* Configuración de la disponibilidad de los plugins */
void BasicPlugin::setEnabled(const bool b)
{
    // Dado que los valores de los estados disponibles están almacenados en los ajustes, los ajustes deben ser cambiados aquí también.
    m_settings.setValue(PLUGIN_STATE_KEY, b);
}

/* Establece el valor de referencia para el tamaño del plugin. (Heredado de QWidget) */
QSize BasicPlugin::sizeHint() const
{
    QFont font = qApp->font();
    font.setFamily("Noto Mono");
    QFontMetrics FM(font);
    return FM.boundingRect("000").size();
}

/* El evento se desencadenó cuando se cambió el tamaño del plugin. (Heredado de QWidget) */
void BasicPlugin::resizeEvent(QResizeEvent *e)
{
    // De hecho, el tamaño de los plugins del Dock son constantes (no se pueden ajustar), por lo que no hay procesamiento adicional, ¡llama al método padre en el bien!
    QWidget::resizeEvent(e);
}

/* Dibuja la interfaz del plugin. Esta es la parte más importante de esta clase, el aspecto del plugin está determinado por esto. (Heredado de QWidget) */
void BasicPlugin::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);

    /* El QPainter se usa aquí para dibujar la interfaz.
     * este es un método manual para dibujar la interfaz.
     * Muchos entornos de programación (por ejemplo, Tkinter para Python, MFC para Windows)
     * sólo pueden escribir interfaces en forma de código.
     * una herramienta de diseño de formas visuales que difiere de Qt y VB.
     * además, el uso del QPainter es análogo a la programación del Canvas de H5.
     */
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);      // Qt tiene su propio motor de renderizado.
    painter.setPen(Qt::white);                          // Establecer el color del pincel

    // Establecer las fuentes
    QFont font = qApp->font();          // Necesario para conseguir una instancia de QFont
    font.setFamily("Noto Mono");
    painter.setFont(font);

    // texto
    painter.drawText(rect().adjusted(2,0,0,0), Qt::AlignLeft | Qt::AlignVCenter, text);
}

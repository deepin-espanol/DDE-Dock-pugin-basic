#ifndef DDE_BASICDOCK_H
#define DDE_BASICDOCK_H

#include <QWidget>
#include <QSettings>

class BasicPlugin : public QWidget
{
    /* Macro Q_OBJECT, marcando esta clase como un objeto Qt.
     * Sólo añadiendo esta macro se puede utilizar la señal en este módulo, de lo contrario el compilador reportará un error.
     * Para usar esta macro, el archivo del proyecto PRO también es necesario añadir la configuración "CONFIG += plugin",
     * de lo contrario ddde-dock no podrá cargar el plugin.
     * De hecho, si no añades Q_OBJECT y no usas la señal en este módulo, el plug-in puede ser cargado,
     * incluso si no cambias la configuración en PRO.
     */
    Q_OBJECT

public:
    explicit BasicPlugin(QWidget *parent = nullptr);           // Constructor

    bool enabled();                     // Devuelve la disponibilidad del plugin
    void setEnabled(const bool b);      // Establecer la disponibilidad del plugin
    void setText(QString t);            //Used to set the text to be displayed and calculate the needed size

/* Metodología requestUpdateGeometry
 * Señales utilizadas por Haitian Hawk en el diseño del plugin que pueden ser
 * usadas para notificar a ddde-dock para actualizar la interfaz del plugin
 * Pero de hecho, la interfaz de usuario del plugin puede ser actualizada como de costumbre sin usar esta señal.
 * Y su código fuente no implementa este método, sólo vincula la señal a m_ProxyInter->itemUpdate.
 * Nota: Si la señal no se utiliza, no es necesario añadir "CONFIG += plugin" en los archivos Q_OBJECT y PRO al principio.
 */

private:
    // Los siguientes tres métodos heredan de QWidget y son ejecutados automáticamente por Qt
    QSize sizeHint() const override;
    void resizeEvent(QResizeEvent *e) override;
    void paintEvent(QPaintEvent *e) override;

    // Ajustes de operación
    QSettings m_settings;
    //The font that we'll use
    QFont m_font;
    // El texto que aparece en el plugin
    QString text;
};

#endif // DDE_BASICDOCK_H

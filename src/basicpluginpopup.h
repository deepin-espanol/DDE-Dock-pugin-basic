#ifndef DDE_BASICDOCKPOPUP_H
#define DDE_BASICDOCKPOPUP_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QDateTime>                // Clase de hora y fecha, usada para obtener la hora y fecha actual
#include <QSettings>

class BasicPluginPopup : public QWidget
{
    Q_OBJECT

public:
    explicit BasicPluginPopup(QWidget *parent = nullptr);

private:
    QSettings m_settings;       // módulo de configuración
    QGridLayout *layout;        // Disposición de los pop-ups
    QLabel *lblTitle, *lblIcon, *lblText, *lblDateTime;     // Pestañas en las ventanas emergentes

    QDate qDate;                                        // Ejemplos de clases de fecha
    QTime qTime;                                        // Ejemplos de clases de tiempo

/* Uso de la función de ranura para actualizaciones de plugins */
public slots:
    void updatePopupUI();
};

#endif // DDE_BASICDOCKPOPUP_H

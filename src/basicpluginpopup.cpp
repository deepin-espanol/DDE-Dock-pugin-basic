#include "basicpluginpopup.h"

#define DATETIME_PLACEHOLDER "Esto muestra la fecha y la hora"

BasicPluginPopup::BasicPluginPopup(QWidget *parent)
    : QWidget(parent),
      m_settings("deepin", "DDEBasicPlugin")      // Iniciar el almacenamiento de la configuración del plugin
{
    /* Usar código puro para construir la interfaz.
     *
     * Los componentes añadidos al diseño pueden ser declarados en la clase antes de ser inicializados aquí.
     * También puedes crearlo e iniciarlo directamente aquí (por ejemplo, QLabel *etiqueta = nueva QLabel).
     * de cualquier manera, pero cabe señalar que el alcance de esta última se limita a los constructores.
     * Esto significa que no podemos cambiar las propiedades de estos componentes en programas posteriores.
     * Así que por favor ten cuidado y sólo usa la última opción si estás seguro de que las propiedades del componente no cambiarán.
     */

    setFixedWidth(300);
    layout = new QGridLayout;

    /* etiqueta de título */
    lblTitle = new QLabel;
    lblTitle->setText(tr("Plugin basico para dde-dock"));
    lblTitle->setStyleSheet("color: white; font-size: 20px; padding-bottom: 10px; ");      // El CSS soportado por Qt es sólo un subconjunto. Tenga en cuenta que la unidad de ajuste de la fuente no puede ser em, rem, etc.
    lblTitle->setAlignment(Qt::AlignCenter);
    layout->addWidget(lblTitle, 0, 0, 1, 2);    // Los cinco parámetros son, en orden: objeto del widget, fila, columna, expansión de la fila y expansión de la columna. Los dos últimos se utilizan para fusionar las células

    /* Etiquetas de la imagen */
    lblIcon = new QLabel;
    lblIcon->setPixmap(QPixmap(":/icons/icon.png").scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    lblIcon->setAlignment(Qt::AlignCenter);
    layout->addWidget(lblIcon, 1, 0);

    /* Pestaña de descripción en el lado derecho de la imagen */
    lblText = new QLabel;
    lblText->setText("plugin test \n Deepin en español");
    lblText->setStyleSheet("color: white; ");
    lblText->setAlignment(Qt::AlignLeft);
    layout->addWidget(lblText, 1, 1);

    /* Etiquetas de fecha y hora */
    lblDateTime = new QLabel;
    lblDateTime->setText(DATETIME_PLACEHOLDER);
    lblDateTime->setStyleSheet("color: white; font-size: 15px; padding-top: 10px; ");
    lblDateTime->setAlignment(Qt::AlignCenter);
    layout->addWidget(lblDateTime, 2, 0, 1, 2);

    setLayout(layout);
}

/* Refrescar Plugin Popup UI */
// Este plugin mostrará: mostrar el reloj, tiempo real en la parte inferior de la ventana.
void BasicPluginPopup::updatePopupUI()
{
    // Consigue la fecha y la hora actuales. Las dos funciones estáticas siguientes crearán nuevas instancias del objeto en base a la hora/fecha actual
    qDate = QDate::currentDate();
    qTime = QTime::currentTime();

    // Consigue el texto de la hora y la fecha en el formato especificado y ponlo en una etiqueta.
    lblDateTime->setText(qDate.toString("dd-MM-yyyy  ") + qTime.toString("HH:mm:ss"));
}

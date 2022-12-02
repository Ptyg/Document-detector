#pragma once

#include "ui_App.h"

#include <QtWidgets/QMainWindow>
#include <QString>

#include "CvImage.h"

class App : public QMainWindow
{
    Q_OBJECT

public:
    App(QWidget* parent = nullptr);
    ~App();
public slots:
    void show_finded_doc();
    void load_image();
    void clear_original_image();
    void save_result();
private:
    void display_original_image();

    Ui::AppClass ui;
    QString picturePath;
};

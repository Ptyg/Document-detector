#include "App.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QPixmap>
#include <QImage>

#include <opencv2/highgui.hpp>

App::App(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    QObject::connect(ui.loadImageBtn, SIGNAL(clicked()), this, SLOT(load_image()));
    QObject::connect(ui.cropImageBtn, SIGNAL(clicked()), this, SLOT(show_finded_doc()));
    QObject::connect(ui.clearImgBtn, SIGNAL(clicked()), this, SLOT(clear_original_image()));
    QObject::connect(ui.saveResultBtn, SIGNAL(clicked()), this, SLOT(save_result()));
}

void App::show_finded_doc() {
    if (picturePath.isEmpty()) {
        QMessageBox msgBox(QMessageBox::Information, "No image loaded", "Load an image before cropping");
        msgBox.exec();
        return;
    }
    if (ui.croppedImg->pixmap() != nullptr) {
        QMessageBox msgBox(QMessageBox::Information, "Result exists", "Result is already exists");
        msgBox.exec();
        return;
    }
    CvImage cvImg(picturePath.toStdString());
    auto img = cvImg.findDoc();
    auto croppedImageLabelSize = ui.croppedImg->size();
    
    QImage image1 = QImage(static_cast<uchar*>(img.data), static_cast<int>(img.cols), 
                           static_cast<int>(img.rows), static_cast<int>(img.step), 
                           QImage::Format_RGB888);

    ui.croppedImg->setPixmap(QPixmap::fromImage(image1));
    ui.croppedImg->setScaledContents(true);
    ui.croppedImg->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
}

void App::display_original_image() {
    auto origImageLabelSize = ui.origImg->size();
    QImage image{ picturePath };

    ui.origImg->setPixmap(QPixmap::fromImage(image));
    ui.origImg->setScaledContents(true);
    ui.origImg->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
}

void App::load_image() {
    picturePath = QFileDialog::getOpenFileName(
        this,
        tr("Choose file"),
        QDir::currentPath(),
        "PNG (*.png);; JPG (*.jpg)"
    );
    if (!picturePath.isEmpty()) {
        display_original_image();
    }
}

void App::clear_original_image() {
    ui.origImg->setText("original image");
    ui.croppedImg->setText("result");
    picturePath.clear();
}

void App::save_result() {
    if (ui.croppedImg->pixmap() == nullptr) {
        QMessageBox msgBox(QMessageBox::Information, "No result to save", "Crop an image before saving");
        msgBox.exec();
        return;
    }
    
    auto filename = QFileDialog::getSaveFileName(
        this,
        tr("Save image"),
        QDir::currentPath(),
        "PNG (*.png);; JPG (*.jpg)"
    );
    if (!filename.isEmpty()) {
        ui.croppedImg->pixmap()->toImage().save(filename);
    }
}

App::~App()
{}

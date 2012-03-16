#include "dialog.h"
#include <common/pam.cpp>
#include <QtCore/QFileInfo>
#include <QtGui/QMouseEvent>
#include <QtCore/QUrl>
#include <common/image.h>

JDiffDialog::JDiffDialog( QDialog *parent /*= 0*/ ) 
	: QDialog(parent) {
	form.setupUi(this);
    setAcceptDrops(true);
}

void JDiffDialog::loadImage(const string &filename, bool &isHDR) {
    string extension = filename.substr(filename.size() - 4);
    if (extension == ".exr") {
        image = loadExr(filename);
        isHDR = true;
    } else if (extension == ".tga") {
        image = loadTga(filename);
        isHDR = false;
    } else if (extension == ".ppm") {
        image = loadPnm3f(filename);
        isHDR = false;
    } else if (extension == ".pfm") {
        image = loadPnm3f(filename);
        isHDR = true;  
    } else {
        image = loadLdr(filename);
        isHDR = false;
    }
}

void JDiffDialog::setImage( const QString &f ) {
}


void JDiffDialog::dragEnterEvent(QDragEnterEvent *event) {
    if (event->mimeData()->hasUrls())
        event->acceptProposedAction();
}

void JDiffDialog::dropEvent(QDropEvent *event) {
    setImage(event->mimeData()->urls()[0].toLocalFile());
    event->acceptProposedAction();
    setFocus();
}

void JDiffDialog::setExposureLabel( float exposure ) {
    QString eStr;
    eStr.sprintf("%.2f", exposure);
    form.exposureLabel->setText(eStr);
}

void JDiffDialog::setGammaLabel( float gamma ) {
    QString gStr;
    gStr.sprintf("%.2f", gamma);
    form.gammaLabel->setText(gStr);
}

void JDiffDialog::setScaleLabel( float scale ) {
    QString sStr;
    sStr.sprintf("%.3f", scale);
    form.scaleLabel->setText(sStr);
}

void JDiffDialog::setCoordinateLabel( int x, int y ) {
    QString cStr;
    cStr.sprintf("[%4d, %4d]", x, y);
    form.coordinateLabel->setText(cStr);
}

void formatNumber(float v, QString &f) {
    if (v != 0.0f && (abs(v) < 0.0001 || abs(v) >= 1000))
        f.sprintf("%#9.2e", v);
    else
        f.sprintf("%9.4f", v);
}

void JDiffDialog::setColorLabel( int x, int y ) {
    QString str;
    if (x >= 0 && x < image.width() && y >= 0 && y < image.height()) {
        const vec3f &c = image.at(x, y);
        QString fx, fy, fz;
        formatNumber(c.x, fx);
        formatNumber(c.y, fy);
        formatNumber(c.z, fz);
        str.append("[").append(fx).append(", ").append(fy).append(", ").append(fz).append("]");
    } else {
        str = "[-----, -----, -----]";
    }
    form.colorLabel->setText(str);
}

**Colorful QR code generator**


This is a QT implementation a QR code generator using the library provided by Nayuki, more info below.
I also have the deployed version uploaded in another folder, if you need it just download it and use it. 

Basically the function here makes everything work.
From the QWidget you create (QMainWindow, QDialog, whatever that inherits QWidget), 
use the paintEvent fuction to call this paintQR function I have wrote.
```c++
void paintQR(QPainter &painter, const QSize sz, const QString &data, QColor bg, QColor fg)
{
    //this code here turns the input into something like this => 1001010101010100000011110010
    qrcodegen::QrCode qr = qrcodegen::QrCode::encodeText(data.toUtf8().constData(), qrcodegen::QrCode::Ecc::LOW);
    //bg background color can be selected from the comboBox which I added to this project
    //or you can just set it to QColor bg = ("white"); (for color names check here : https://www.w3.org/TR/SVG11/types.html#ColorKeywords)
       
    painter.setBrush(bg);     
    painter.setPen(Qt::NoPen);
    painter.drawRect(0,0,400,556);

    const int s=qr.getSize()>0?qr.getSize():1;
    const double w=sz.width();
    const double h=sz.height();
    const double aspect=w/h;
    const double size=((aspect>1.0)?h:w);
    const double scale=size/(s+2);
     
     //now this part paints the foreground of the QR code
     //Again for the color you can just set this to black if you do not wish to add color changing functions to your build.
     //now we read the whatever 00101010101010000 and paint

    painter.setPen(Qt::NoPen);
    painter.setBrush(fg);
    for(int y=0; y<s; y++) {
        for(int x=0; x<s; x++) {
            const int color=qr.getModule(x, y);  // 0 for no draw, 1 for draw
            if(0!=color) {
                const double rx1=(x+1)*scale;
                const double ry1=(y+1)*scale;
                QRectF r(rx1, ry1, scale, scale);
                painter.drawRects(&r,1);
            }
        }
    }
}


void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    paintQR(painter,QSize(400,400),MainWindow::line->toPlainText(),bgColor->currentText(), fgColor->currentText());
}
```






You can find his code here: 
https://github.com/nayuki/QR-Code-generator/tree/master/cpp


This is the README from Nayuki's C++ QR code generator source files.

QR Code generator library - C++
Introduction

This project aims to be the best, clearest QR Code generator library. The primary goals are flexible options and absolute correctness. Secondary goals are compact implementation size and good documentation comments.

Home page with live JavaScript demo, extensive descriptions, and competitor comparisons: https://www.nayuki.io/page/qr-code-generator-library
Features

Core features:

   Significantly shorter code but more documentation comments compared to competing libraries
   Supports encoding all 40 versions (sizes) and all 4 error correction levels, as per the QR Code Model 2 standard
   Output format: Raw modules/pixels of the QR symbol
   Detects finder-like penalty patterns more accurately than other implementations
   Encodes numeric and special-alphanumeric text in less space than general text
   Coded carefully to prevent memory corruption, integer overflow, platform-dependent inconsistencies, and undefined behavior; tested rigorously to confirm safety
   Open-source code under the permissive MIT License

Manual parameters:

   User can specify minimum and maximum version numbers allowed, then library will automatically choose smallest version in the range that fits the data
   User can specify mask pattern manually, otherwise library will automatically evaluate all 8 masks and select the optimal one
   User can specify absolute error correction level, or allow the library to boost it if it doesn't increase the version number
   User can create a list of data segments manually and add ECI segments

More information about QR Code technology and this library's design can be found on the project home page.

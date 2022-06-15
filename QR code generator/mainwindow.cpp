#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qrcodegen.h"
//Since I added the choose color function, I had to list all the color names listed : https://www.w3.org/TR/SVG11/types.html#ColorKeywords
QStringList colors = {
    "antiquewhite",
    "aqua",
    "aquamarine",
    "azure",
    "beige",
    "bisque",
    "black",
    "blanchedalmond",
    "blue",
    "blueviolet",
    "brown",
    "burlywood",
    "cadetblue",
    "chartreuse",
    "chocolate",
    "coral",
    "cornflowerblue",
    "cornsilk",
    "crimson",
    "cyan",
    "darkblue",
    "darkcyan",
    "darkgoldenrod",
    "darkgray",
    "darkgreen",
    "darkgrey",
    "darkkhaki",
    "darkmagenta",
    "darkolivegreen",
    "darkorange",
    "darkorchid",
    "darkred",
    "darksalmon",
    "darkseagreen",
    "darkslateblue",
    "darkslategray",
    "darkslategrey",
    "darkturquoise",
    "darkviolet",
    "deeppink",
    "deepskyblue",
    "dimgray",
    "dimgrey",
    "dodgerblue",
    "firebrick",
    "floralwhite",
    "forestgreen",
    "fuchsia",
    "gainsboro",
    "ghostwhite",
    "gold",
    "goldenrod",
    "gray",
    "grey",
    "green",
    "greenyellow",
    "honeydew",
    "hotpink",
    "indianred",
    "indigo",
    "ivory",
    "khaki",
    "lavender",
    "lavenderblush",
    "lawngreen",
    "lemonchiffon",
    "lightblue",
    "lightcoral",
    "lightcyan",
    "lightgoldenrodyellow",
    "lightgray",
    "lightgreen",
    "lightgrey",
    "lightpink",
    "lightsalmon",
    "lightseagreen",
    "lightskyblue",
    "lightslategray",
    "lightslategrey",
    "lightsteelblue",
    "lightyellow",
    "lime",
    "limegreen",
    "linen",
    "magenta",
    "maroon",
    "mediumaquamarine",
    "mediumblue",
    "mediumorchid",
    "mediumpurple",
    "mediumseagreen",
    "mediumslateblue",
    "mediumspringgreen",
    "mediumturquoise",
    "mediumvioletred",
    "midnightblue",
    "mintcream",
    "mistyrose",
    "moccasin",
    "navajowhite",
    "navy",
    "oldlace",
    "olive",
    "olivedrab",
    "orange",
    "orangered",
    "orchid",
    "palegoldenrod",
    "palegreen",
    "paleturquoise",
    "palevioletred",
    "papayawhip",
    "peachpuff",
    "peru",
    "pink",
    "plum",
    "powderblue",
    "purple",
    "red",
    "rosybrown",
    "royalblue",
    "saddlebrown",
    "salmon",
    "sandybrown",
    "seagreen",
    "seashell",
    "sienna",
    "silver",
    "skyblue",
    "slateblue",
    "slategray",
    "slategrey",
    "snow",
    "springgreen",
    "steelblue",
    "tan",
    "teal",
    "thistle",
    "tomato",
    "turquoise",
    "violet",
    "wheat",
    "white",
    "whitesmoke",
    "yellow",
    "yellowgreen"

};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("QR Generator");
    setFixedSize(400,556);
    gen = new QPushButton("Generate", this);
    gen -> setGeometry(295,448,92,92);

    line = new QTextEdit("Welcome to QR generator, enter anything!",this);
    line -> setGeometry(17,449,270,90);

    connect(gen, SIGNAL(clicked(bool)), this, SLOT(update()));

    fgColor = new QComboBox(this);
    fgColor -> addItems(colors);
    fgColor -> setCurrentText("navy");
    fgColor -> setGeometry(17,403,180,30);

    bgColor = new QComboBox(this);
    bgColor -> addItems(colors);
    bgColor -> setCurrentText("darkgoldenrod");
    bgColor -> setGeometry(205,403,180,30);

    connect(fgColor, SIGNAL(textActivated(const QString &)), this, SLOT(update()));
    connect(bgColor, SIGNAL(textActivated(const QString &)), this, SLOT(update()));
}



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
        
        //now this part paints the foreground of the QR code.
        //Again for the color you can just set this to black if you do not wish to add color changing functions to your build.
        //now we read the whatever 00101010101010000 and paint
        
        painter.setPen(Qt::NoPen);
        painter.setBrush(fg);
        for(int y=0; y<s; y++) {
            for(int x=0; x<s; x++) {
                const int color=qr.getModule(x, y);  // 0 for no draw, 1 for draw
                if(0!=color) {
                    const double rx1=(x+1)*scale, ry1=(y+1)*scale;
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



MainWindow::~MainWindow()
{
    delete ui;

}


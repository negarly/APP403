#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <QWidget>
#include <QTimer>
#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QDebug>

gamewindow::gamewindow(QWidget *parent)
    : QMainWindow(parent), currentBackgroundIndex(0)
    , ui(new Ui::gamewindow)
{
    ui->setupUi(this);
    backgrounds = {"C:/Users/Techno/Downloads/3D_cube_generated.jpg",
                   "C:/Users/Techno/Downloads/Abstract_hologram_hi-tech_background_generated.jpg",
                   "C:/Users/Techno/Downloads/vecteezy_hologram-podium-futuristic-circle-blue-vector_8450118.jpg",
                   "C:/Users/Techno/Downloads/vecteezy_futuristic-sci-fi-glowing-hud-element-and-particle_5550030.jpg",
                   "C:/Users/Techno/Downloads/Abstract_background_generated.jpg" };

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    backgroundLabel = new QLabel(centralWidget);
    layout->addWidget(backgroundLabel);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &gamewindow::changeBackground);
    timer->start(20000);

    changeBackground();

    backgroundLabel->setScaledContents(true);
}

void gamewindow:: changeBackground() {
    if (backgrounds.isEmpty())
        return;

    QString imagePath = backgrounds[currentBackgroundIndex];
    QPixmap pixmap(imagePath);
    pixmap = pixmap.scaled(backgroundLabel->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    backgroundLabel->setPixmap(pixmap);
    // backgroundLabel->setStyleSheet("background-image: url(" + imagePath + "); background-repeat: no-repeat; background-position: center;");
    currentBackgroundIndex = (currentBackgroundIndex + 1) % backgrounds.size();
}
gamewindow::~gamewindow()
{
    delete ui;
}

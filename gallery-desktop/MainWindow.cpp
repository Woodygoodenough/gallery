#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QItemSelectionModel>
#include <QStackedWidget>

#include "AlbumModel.h"
#include "GalleryWidget.h"
#include "PictureModel.h"
#include "PictureWidget.h"
#include "ThumbnailProxyModel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mGalleryWidget(new GalleryWidget(this))   //set up child widget from parent one
    , mPictureWidget(new PictureWidget(this))
    , mStackedWidget(new QStackedWidget(this))
{
    ui->setupUi(this);

    AlbumModel *albumModel = new AlbumModel(this);
    QItemSelectionModel *albumSelectionModel = new QItemSelectionModel(albumModel, this);
    mGalleryWidget->setAlbumModel(albumModel);
    mGalleryWidget->setAlbumSelectionModel(albumSelectionModel);

    PictureModel *pictureModel = new PictureModel(*albumModel, this);
    ThumbnailProxyModel *thumbnailModel = new ThumbnailProxyModel(this);
    thumbnailModel->setSourceModel(pictureModel);

    QItemSelectionModel *pictureSelectionModel = new QItemSelectionModel(thumbnailModel, this);
    mGalleryWidget->setPictureModel(thumbnailModel);
    mGalleryWidget->setPictureSelectionModel(pictureSelectionModel);
    mPictureWidget->setModel(thumbnailModel);
    mPictureWidget->setSelectionModel(pictureSelectionModel);

    connect(mGalleryWidget, &GalleryWidget::pictureActivated, this, &MainWindow::displayPicture);

    connect(mPictureWidget, &PictureWidget::backToGallery, this, &MainWindow::displayGallery);

    mStackedWidget->addWidget(mGalleryWidget);
    mStackedWidget->addWidget(mPictureWidget);
    displayGallery();

    setCentralWidget(mStackedWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::displayGallery()
{
    mStackedWidget->setCurrentWidget(mGalleryWidget);
}

void MainWindow::displayPicture(const QModelIndex & /*index*/)
{
    mStackedWidget->setCurrentWidget(mPictureWidget);
}

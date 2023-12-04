#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->addPassButton, &QPushButton::clicked, this, &MainWindow::onAddMusicButtonClicked);
    connect(ui->editPassButton, &QPushButton::clicked, this, &MainWindow::onEditMusicButtonClicked);
    connect(ui->deletePassButton, &QPushButton::clicked, this, &MainWindow::onDeleteMusicButtonClicked);
    connect(ui->saveToFileButton, &QPushButton::clicked, this, &MainWindow::onSaveButtonClicked);
    connect(ui->loadFromFileButton, &QPushButton::clicked, this, &MainWindow::onLoadButtonClicked);

    loadFromFile();
    updateMusicList();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateMusicList() {
    ui->musicListWidget->clear();
    for(const auto& music : musicManager.keys()) {
        QString formattedMusic = QString("%1 - %2").arg(music).arg(musicManager.value(music));
        ui->musicListWidget->addItem(formattedMusic);
    }
}

void MainWindow::onAddMusicButtonClicked() {
    QString musicTitle = ui->addMusicTitleLineEdit->text();
    QString musicValue = ui->addMusicValueLineEdit->text();

    if(!musicTitle.isEmpty() && !musicValue.isEmpty()) {
        addMusic(musicTitle, musicValue);
        updateMusicList();
    }
}

void MainWindow::onEditMusicButtonClicked() {
    QListWidgetItem* selectedMusic = ui->musicListWidget->currentItem();
    if(selectedMusic) {
        QString currentTitle = selectedMusic->text().section('-', 0, 0).trimmed();
        QString newTitle = ui->editMusicTitleLineEdit->text();
        QString newValue = ui->editMusicValueLineEdit->text();

        if(!newTitle.isEmpty() && !newValue.isEmpty()) {
            editMusic(currentTitle, newTitle, newValue);
            updateMusicList();
        }
    }
}

void MainWindow::onDeleteMusicButtonClicked() {
    QListWidgetItem* selectedMusic = ui->musicListWidget->currentItem();
    if(selectedMusic) {
        QString currentTitle = selectedMusic->text().section('-', 0, 0).trimmed();
        musicManager.remove(currentTitle);
        updateMusicList();
    }
}

void MainWindow::onSaveButtonClicked() {
    saveToFile();
}

void MainWindow::onLoadButtonClicked() {
    loadFromFile();
    updateMusicList();
}

void MainWindow::saveToFile() {
    QFile file("music.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);

        for(const auto& music : musicManager.keys()) {
            out << music << " - " << musicManager.value(music) << "\n";
        }

        file.close();
    }
}

void MainWindow::loadFromFile() {
    QFile file("music.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);

        musicManager.clear();

        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split(" - ");
            if (parts.size() == 2) {
                musicManager.insert(parts[0], parts[1]);
            }
        }

        file.close();
    }
}

void MainWindow::addMusic(const QString &title, const QString &music) {
    musicManager.insert(title, music);
}

void MainWindow::editMusic(const QString &currentTitle, const QString &newTitle, const QString &newValue) {
    musicManager.remove(currentTitle);
    musicManager.insert(newTitle, newValue);
}

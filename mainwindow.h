#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QString>
#include <QFile>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onAddMusicButtonClicked();
    void onEditMusicButtonClicked();
    void onDeleteMusicButtonClicked();
    void onSaveButtonClicked();
    void onLoadButtonClicked();


private:
    Ui::MainWindow *ui;
    QMap<QString, QString> musicManager;
    void updateMusicList();
    void saveToFile();
    void loadFromFile();
    void addMusic(const QString &title, const QString &music);
    void editMusic(const QString &currentTitle, const QString &newTitle, const QString &newValue);
};

#endif // MAINWINDOW_H

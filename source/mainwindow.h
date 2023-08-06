#ifndef ADC_MAIN_WINDOW_H

#define ADC_MAIN_WINDOW_H

#include <QMainWindow>

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
    void on_action_Load_triggered();
    
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

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
    
    void on_Dump_Loaded();
    
    void on_action_Load_triggered();
    
    void on_action_Exit_triggered();
    
    void on_action_Export_triggered();
    
    void on_action_Save_triggered();
    
    void on_action_Scope_triggered();
    
    void on_action_Samples_triggered();
    
    void on_action_Options_triggered();
    
    void on_action_Tools_triggered();
    
    void on_action_Info_triggered();
    
    void on_action_FullScreen_triggered();
    
    void on_action_DefaultView_triggered();
    
    void on_action_AlwaysOnTop_triggered();
    
    void on_action_CompactView_triggered();
    
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

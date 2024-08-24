#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QString>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void buttonClicked();
  bool test_sign(const QChar ch);
  bool is_func(QString func);
  bool is_operand(QChar op);
  bool check_error(QString str);
  void C_click();
  void AC_click();
  void equal_click();
  void replase_nan();
  void on_toolButton_clicked();

 private:
  Ui::MainWindow *ui;
  bool eqButtonClicked;
};
#endif  // MAINWINDOW_H

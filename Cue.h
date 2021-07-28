#ifndef CUE_H
#define CUE_H

#include<QGraphicsRectItem>
#include<QObject>  //!!!!
#include<QPaintEvent>
#include<QPainter>
#include<QWidget>
#include<QGraphicsItem>
#include<QStyleOptionGraphicsItem>
#include<QFont>
#include<QPoint>
#include<QDebug>
#include<QTimer>
#include<QMainWindow>

class Cue:public QObject,public QGraphicsItem{
    Q_OBJECT
public:
    Cue(QGraphicsItem *parent =nullptr);
    void setCuePower(double);   //устанавливает мощность удара кия
    double getPower();  //возвращает
    static double getMaxPower();
protected:
    QRectF boundingRect() const;
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);
    ///////////////////////////////////VARIABLE///////////////
protected:
    QVector<QPointF> vector;    //вектор контура кия
    double scale;   //сквозной масштаб
    double alpha;   //уголповорота
    QTimer  * cueTimer; //таймер для увеличения силы удара вовремя зажатой кноки мыши
    double power{0.};   //сила удара
    static double maxPower;     //максимальная сила удара
    double deltaPower{40.};     //шаг приращения силы удара
public slots:
    void gainPower();       //увеличивает силу удара каждый тик таймера
    ///////////FRIENDS////////////////
    friend class MainWindow;
    friend class MyGraphicsView;
};

#endif // CUE_H

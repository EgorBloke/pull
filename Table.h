#ifndef TABLE_H
#define TABLE_H

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
#include"Pocket.h"

class Table : public QObject,public QGraphicsItem
{
    Q_OBJECT
public:

    Table(double maxHeight = 800, QObject *parent = nullptr);
    double getScale(); //установка масштаба
    double getClothWidht();     //возвращает ширину поля стола
    double getClothHeight();    // длину
    QPointF getWhiteBallWaitingPos();   //поле белого шара для отрисовки при попадании в лузу
    QPointF getBlackBallWaitingPos();   //то же для черного шара
protected:
    QRectF boundingRect() const;
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);

///////////////////////////////////VARIABLE///////////////

    QList<QPointF> vecInside;       //контур стола внешний
    QList<QPointF> vecOutside;      //внутренний
    QColor insideColor;
    QColor outsideColor;
    double tableHeight;         //размеры
    double clothWidht;
    double clothHeight;

    const double static defaultTableHeight;     //размеры по умолчнанию
    const double static defaultClothWidht;
    const double static defaultClothHeight;
    const double static defaultBallRadius;
    const double static defaultBoardSize;
    double  boardSize;

    double ballRadius;      //радиус шара
    double scale;       //сквозной масштаб

    QPointF blackBallWaitingPos=QPointF(350,100);
    QPointF whiteBallWaitingPos=QPointF(390,100);

    QPointF firstPlayerPos{};       //позиция для отрисовки игроков
    QPointF secondPlayerPos{};
};

#endif // TABLE_H

#ifndef PLAYER_H
#define PLAYER_H
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

#include"Ball.h"
#include"Cue.h"



class Player : public QObject, public QGraphicsItem
{
public:
    enum class BallType{ PAINTED=1, STRIPPED,WHITE,BLACK, NO_TYPE };
//    class Ball;
    Q_OBJECT
public:
    Player(QString name="Player", double ballRadius=57, QGraphicsItem *parent = nullptr);
    bool isLastBall();      //возвращает истину, если игроку осталось забить только 8 шар
    bool isActive();        //истина если игрок владеет ходом
    bool isPreparingKick();     //истина если сработал сработал обработчик нажатися кнопки мыши
    void addBallToShelf();      //добавляет шар на полку игрока
    void setBallType(BallType);     //закрепляет за игроком тип шара в текущей игре
    void setPreparingKickStatus(bool);  //устанавливает статус подготовки к удару
    QString getName();
    BallType getBallType();
    int getBallCount();
    void raiseBallCount(int);   //увеличивает число забитых шаров
    QPointF getNextBallShelfPoint();        //возвращает координаты для следующего шара на полке
    void setActiveStatus(bool);
protected:
    QRectF boundingRect() const;
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget);
 ////////VARIABLES
 protected:
    QFont *_font;
    QString name{};
    int ballCount{0};       //колчиество забитых шаров в игре
    QVector<QPointF> ballsPos;      //вектор с координатами шаров на полке
    QPointF firstBallPos{};
    QPointF labelBallPos{};
    BallType ballType{BallType::NO_TYPE};
    bool lastBallStatus{false};
    bool active{false};
    bool preparingKick{false};
    double ballRadius;

    friend class MainWindow;
    friend class Cue;
};

inline Player::BallType Player::getBallType()
{
    return ballType;
}

#endif // PLAYER_H

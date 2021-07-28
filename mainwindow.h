
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QGraphicsItem>
#include<QGraphicsScene>
#include<QVector>
#include <QGraphicsView>
#include<QTimer>
#include<QMouseEvent>
#include<QMessageBox>
#include"MyScene.h"

#include"Pocket.h"
#include"Coord.h"
#include"Ball.h"
#include"Cue.h"
#include"Table.h"
#include"Pocket.h"
#include"Player.h"



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Player;
/////////////////////MainWindow//////////////////
class MainWindow : public QMainWindow
{
Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr, bool ii=false);
    ~MainWindow();

private:

    Ui::MainWindow *ui{nullptr};
    QGraphicsScene * scene{nullptr};  //main scene
    QGraphicsScene * sceneSub{nullptr};

    QList<Ball*> Balls;				//вектор всех шаров
    QTimer * timer{nullptr};        //main timer
    Cue *cue{nullptr};          //кий
    Table * table{nullptr};     //стол
    QVector<Pocket*> pockets;   //массив луз
    Player * player1{nullptr};      //игрок 1
    Player * player2{nullptr};      //игрок 2
    QVector<Ball**> ballsInPocket;      //вектор шаров забитых в лузу на этом ходу
    Player **activePlayer{&player1};    //указатель на активного игрока


    QVector<Coord> defaultBallsCoords;     //Вектор координат шаров по умлочанию в треугольнике при расстановке
    static Coord firstBallPosition;					//координаты первого шара


    double windowHeight{620};       //размер окна приложения для рассчета общего масштаба

    double height{0};       //высота стола
    double width {0};       //ширина стола
    double scale{1};        //текущий масштаб всех элементов
   Coord angleBallCoords{Coord(0,0)}; //координата первого шара с пирамиде

   static double deltaForce;        //изменение static double deltaV*=deltaForce;
   const static double deltaVDefault;		//коэффициент замедления скорости с каждой итерацией
   static double deltaV;        //v*=deltaV
   static double deltaT;		//шаг времени для каждой итерации
   static double deltaVmin;     //минимальное изменение скорости для статуса шара isMoving()
   double deltaPocket{0};         //зазор в лузе
   double pocketSize{0};          //ширина лузы


   bool ballsMoving{false};   //дивгаются ли шары
   bool gameActive{false};      //активна ли игра
   bool foul{false}; //статус фола
   bool whiteBallInPocket{false}; //забит белый шар
   bool blackBallInPocket{false};       //забит черный шар
   bool noBallsInPocket{true};  //не забито шаров
   bool firstHit{true};    //первый удар кием за партию
   bool ballsTouch{false};     //касание шара
   bool sameBallInPocket{false};  //в лузах шары одного типа
   bool noBallTouch{true};      //не было касания шаров
   bool playerBallTypeDefined{false};       //определен тип шаров для игроков
   bool firstTouch{false};  //было ли касание с шаром
   Ball** firstTouchedBall{nullptr}; //Первый коснувшийся шар

   bool ii{false};  //
   double iiScale{0.3}; //
public:
   QPointF firstPlayerPos=QPointF(330,20);  //позиция для отрисовки объекта первого игрока
   QPointF secondPlayerPos=QPointF(330,200);
   int TABLE_OFFSET_X=50;       //смещения координат
   int TABLE_OFFSET_Y=50;

   int SCENE_OFFSET_X=-120;
   int SCENE_OFFSET_Y=-10;

   int SCENE_SIZE_X =702;
   int SCENE_SIZE_Y =852;
public slots:
    ////////////
    void pitch();       //просчет кадра
    /////////////


private slots:
    void on_NewGameBtn_clicked();
    void on_ClearBtn_clicked();
    void on_stopBalls_clicked();
    void on_IIMoveBtn_clicked();
public:


    bool isGameActive();
    bool isFoul();
    bool isTouched();
    bool iSii();
    bool isFirstHit();
    bool isWhiteInPocket();
    bool isBlackInPocket();
    bool isNoBallsInPocked();
    bool isSameBallInPocket();
    bool isNoBallTouched();
    bool isPlayerBallTypeDefined();
    bool isFirstTouch();
public:
    void setII(bool);
    void gameOver();
    void loseGame(Player*);
    void winGame(Player*);


    void setWhiteBallSpeed(double alpha, double impulse);				//устанавливает скорость для битка и добавляет его первым в список движущихся шаров

    void setWhiteBallPosition();		//установка позиции белого шара
//    void setHandleWhiteBallPosition();
    void setWhiteFoulPosition();        //установка белого шара в начальную позицию
    void setBallsDefaultPosition();		//устанавливаем всем шарам координаты из списка дэфолтных координат defaultBallsCoords
    void setCalculetedStatusFalse();    //устанавливает всем активным шарам статус "не просчитаны"
    void calcBallsDistances();		//расчет текущих дистанци между шарами
    void boardCollision();      //проверка столкновения с бортом
    void moveBalls();       //просчет движения всех активных шаров
    void pocketChech();     //проверка попадания в лузу

    void checkPocketedBalls();  //проверка забиты в лузу шаров

    //////////////////
    void setNewGame();
    //////////////////
    void changeMove();      //меняет ход игрока при фоле
    void goOn();        //продолжение хода
    /////////////////


    void generateBallDefaultPosition();     //генерирует координаты шаров в пирамиде
    void setGameScene();    //установка сцены
    void setTable();    //установка стола
    void setScale();    //установка сквозного масштаба
    void setWidht();    //установка размеров
    void setHeight();
    void setBallsScale();
    void setAngleBallCoord();      //уставнока координат углового шара
    void setStartView();    //установка вида пр запускек приложения
    void setBalls();        //добавления шаров на стол
    void setCue();      //добавление кия
    void setCuePosition();      //установка кия к белому шару
    void setCueRotation(QPointF point); // установка угла вращения кия
    void setPockets();  //установка луз
    void setPlayers();  //установка игроков на сцену
    void setPlayersActiveStatus();  //установка статуса игрокам

    void setGameActiveStatus(bool);
    void setFoulStatus(bool);
    void setWhiteBallInPocket(bool);
    void setBlackBallInPocket(bool);
    void setNoBallsInPocket(bool);
    void setTouchStatus(bool);
    void setFirstHitStatus(bool);
    void setSameBallInPocketStatus(bool);
    void setDeltaVDefault();
    void setFirstTouchedBall(Ball**);
    void setNoBallTouchStatus(bool);
    void setBallsInMoving(bool);
    void setPlayerBallTypeDefinedStatus(bool);
    void setFirstTouchStatus(bool);
    bool ballsInMoving();


    /////////////////GET MAIN OBJECTS////////////
    Ball& getFirstTouchedBall();
    Ball &whiteBall();
    Ball &blackBall();
    Player& getActivePlayer();
    Player& getWaitingPlayer();

protected:

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent * );

friend class Ball;
friend class V;
friend class Player;
////////////!!!FOR TESTING!!!//////////
public:
void _setSpeedForAllBall();
void _moveBallsTest();
void setTestPosition();
void clearScene();
void clearTable();
void setTestObjects();
void _setBalls_TEST();
QVector<Ball*> _calcBallsDistances_TEST();

};
#endif // MAINWINDOW_H

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Coord.h"
#include"algorithm"
#include<QtMath>
#include<QWidget>
#include<Coord.h>


extern MainWindow * w;
//Coord MainWindow::firstBallPosition(635.0, 600.0);		//начальная позиция первого шара
double MainWindow::deltaVmin = 0.005;        //шаг счетчика
double MainWindow::deltaForce = 0.9999999999;
const double MainWindow::deltaVDefault = 0.99975;		//коэффициент замедления скорости с каждой итерацией
double MainWindow::deltaV;
double MainWindow::deltaT = 0.0001;		//шаг времени для каждой итерации

/////////////////////////////
MainWindow::MainWindow(QWidget *parent, bool ii) : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer();       //инициализация таймера
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(pitch()));
                    //соединение таймера со слотом просчета игрового кадра
    setStartView();  //установка стартового вида
}

//////////////////////////////
void MainWindow::setNewGame()
{
    setBallsInMoving(false);
    setGameActiveStatus(false);
    setFoulStatus(false);
    setWhiteBallInPocket(false);
    setBlackBallInPocket(false);
    setNoBallsInPocket(true);
    setFirstHitStatus(true);
    ballsTouch=false;
    setSameBallInPocketStatus(false);
    setNoBallTouchStatus(true);
    setPlayerBallTypeDefinedStatus(false);
    setFirstTouchStatus(true);
    setFirstTouchedBall(nullptr);


    goOn();
    setBalls();
//    _setBalls_TEST();
    setCue();
    setPlayers();
//    setPockets();
    deltaPocket = Ball::r*(1.44-1);
    setMouseTracking(true);
    setGameActiveStatus(true);
}

//QPair<double, double> MainWindow::IIMove()
//{
////    MainWindow * w;
////    w = new MainWindow(this,true);
////    w->show();

//////    MainWindow w;

//////    w.show();
////    //    w->setMouseTracking(true);


////    QMessageBox::about(this,"II mode","II mode active");
////    delete w;
////    return qMakePair<double,double>(0,0);

//}



void MainWindow::setGameActiveStatus(bool status)
{
    gameActive = status;
}

bool MainWindow::isGameActive()
{
    return gameActive;
}

void MainWindow::setGameScene()
{
    if (scene){
        delete scene;
    }
//    double k=iiScale*1;
    scene=new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);


    ui->graphicsView->resize(SCENE_SIZE_X,SCENE_SIZE_Y);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
//        ui->graphicsView->setFixedSize(652,852);
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    scene->setSceneRect(SCENE_OFFSET_X,SCENE_OFFSET_Y,SCENE_SIZE_X-2,SCENE_SIZE_Y-2);
    scene->setBackgroundBrush(QBrush(QImage(":/img/flore.jpg")));
//   setHorizontalScrollBarPolicy((Qt::ScrollBarAlwaysOff));       //off scrolling
//    setVerticalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
}

void MainWindow::setTable()
{
    if(table){

        table->deleteLater();
    }

    if(iSii()){
        table = new Table(windowHeight,this);
    }
    else{
        table = new Table(windowHeight,this);
    }

    scene->addItem(table);
    if(iSii()){
        table->setPos(TABLE_OFFSET_X*iiScale,TABLE_OFFSET_Y*iiScale);
    }
    else{
        table->setPos(TABLE_OFFSET_X,TABLE_OFFSET_Y);
    }
}

void MainWindow::setScale()
{
    this->scale=table->getScale();
}

void MainWindow::setWidht()
{
    width=table->getClothWidht();
}

void MainWindow::setHeight()
{
    height=table->getClothHeight();
}

void MainWindow::setBallsScale()
{
    Ball::setBallRadius(scale);
}

void MainWindow::setAngleBallCoord()
{
    angleBallCoords=Coord(table->getClothWidht()/2,table->getClothHeight()*0.3);      //already scaled!!!!!
}

void MainWindow::setStartView()
{
    setGameScene();
    setTable();
    setScale();
    setBallsScale();

    setWidht();
    setHeight();
    setPockets();
    setPlayers();
}

void MainWindow::setBalls()
{
    //set balls

     Balls.clear();
     Balls.emplace_back(new Ball(Coord(), 0, Qt::white, Ball::Type::WHITE,table->getScale(),table));

     Balls.emplace_back(new Ball(Coord(), 1, Qt::yellow, Ball::Type::PAINTED,table->getScale(),table));
     Balls.emplace_back(new Ball(Coord(), 2, Qt::blue, Ball::Type::PAINTED,table->getScale(),table));
     Balls.emplace_back(new Ball(Coord(), 3, Qt::red, Ball::Type::PAINTED,table->getScale(),table));
     Balls.emplace_back(new Ball(Coord(), 4, QColor(QRgb(0x6600cc)), Ball::Type::PAINTED,table->getScale(),table));
     Balls.emplace_back(new Ball(Coord(), 5, QColor(QRgb(0xfa9a00)), Ball::Type::PAINTED,table->getScale(),table));
     Balls.emplace_back(new Ball(Coord(), 6, Qt::green, Ball::Type::PAINTED,table->getScale(),table));
     Balls.emplace_back(new Ball(Coord(), 7, QColor(QRgb(0x331a00)), Ball::Type::PAINTED,table->getScale(),table));

     Balls.emplace_back(new Ball(Coord(), 8, Qt::black, Ball::Type::BLACK,table->getScale(),table));

     Balls.emplace_back(new Ball(Coord(), 9, Qt::yellow, Ball::Type::STRIPPED,table->getScale(),table));
     Balls.emplace_back(new Ball(Coord(), 10, Qt::blue, Ball::Type::STRIPPED,table->getScale(),table));
     Balls.emplace_back(new Ball(Coord(), 11, Qt::red, Ball::Type::STRIPPED,table->getScale(),table));
     Balls.emplace_back(new Ball(Coord(), 12, QColor(QRgb(0x6600cc)), Ball::Type::STRIPPED,table->getScale(),table));
     Balls.emplace_back(new Ball(Coord(), 13, QColor(QRgb(0xfa9a00)), Ball::Type::STRIPPED,table->getScale(),table));
     Balls.emplace_back(new Ball(Coord(), 14, Qt::green, Ball::Type::STRIPPED,table->getScale(),table));
     Balls.emplace_back(new Ball(Coord(), 15, QColor(QRgb(0x331a00)), Ball::Type::STRIPPED,table->getScale(),table));

     setWhiteBallPosition();
     setBallsDefaultPosition();      //set balls coordinates in random order
//    setTestPosition();          //!!!!!!!!TEST!!!!

    for(auto &ball:Balls)
    {
        scene->addItem(ball);
        ball->setPos(ball->x0, ball->y0);
    }
//        _setSpeedForAllBall();      //!!!TEST!!!!
}

void MainWindow::setCue()
{
    if(cue){
        delete cue;
    }
    cue = new Cue(table);

    scene->addItem(cue);
    setCuePosition();}

void MainWindow::setCuePosition()
{
    cue->show();
    cue->setPos(whiteBall().x(),whiteBall().y());

    cue->setRotation(90);
}

Ball &MainWindow::whiteBall()
{
    return *Balls[0];
}

Ball &MainWindow::blackBall()
{
    return *Balls[8];
}

Player &MainWindow::getActivePlayer()
{
    return **activePlayer;
}

Player &MainWindow::getWaitingPlayer()
{
    return (*activePlayer==player1)?*player2:*player1;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setII(bool status)
{
    ii=status;
}

void MainWindow::gameOver()
{
//    timer->stop();
//    clearTable();
//    setNewGame();
//    scene->update();
//    setGameActiveStatus(true);
    clearTable();
    setGameActiveStatus(false);
}

void MainWindow::loseGame(Player * player)
{
    QMessageBox::about(this,"Game over! ",getWaitingPlayer().name+" has won the game");
    gameOver();
    qDebug()<<player->getName()<<"lose";
}

void MainWindow::winGame(Player * player)
{

    qDebug()<<player->getName()<<"lose";
}

void MainWindow::setWhiteBallSpeed(double alpha, double impulse)
{
    whiteBall().setV(-impulse*cos(alpha),-impulse*sin(alpha));
}

bool MainWindow::isFoul()
{
    return foul;
}

bool MainWindow::isTouched()
{
    return ballsTouch;
}

bool MainWindow::iSii()
{
    return ii;
}

bool MainWindow::isFirstHit()
{
    return firstHit;
}



bool MainWindow::isWhiteInPocket()
{
    return whiteBallInPocket;
}

bool MainWindow::isBlackInPocket()
{
    return blackBallInPocket;
}

bool MainWindow::isNoBallsInPocked()
{
    return noBallsInPocket;
}

bool MainWindow::isSameBallInPocket()
{
    return sameBallInPocket;
}

bool MainWindow::isNoBallTouched()
{
    return noBallTouch;
}

bool MainWindow::isPlayerBallTypeDefined()
{
    return playerBallTypeDefined;
}

bool MainWindow::isFirstTouch()
{
    return firstTouch;
}



void MainWindow::setWhiteBallPosition()
{

    Balls[0]->x0=(table->getClothWidht()/2 + (double)(rand()%30)/100);         //WITH SCALE!!!!
    Balls[0]->y0=table->getClothHeight()*0.6;

}

//void MainWindow::setHandleWhiteBallPosition()       //FIX IT!!!!
//{
////    Balls[0]->x0=(table->getClothWidht()/2 + (double)(rand()%30)/100);         //WITH SCALE!!!!
////    Balls[0]->y0=table->getClothHeight()*0.6;
//}

void MainWindow::setWhiteFoulPosition()
{
    QPointF pos(table->getClothWidht()/2 + (double)(rand()%30)/100,table->getClothHeight()*0.6);
    whiteBall().setPos(pos);
    bool isIntersect=true;
    for(auto ball:Balls)
    {
        isIntersect=true;
        if(ball->isActive()&&!(ball->number==0))
        {
            while(isIntersect)
            {
                if(whiteBall().distance(*ball)<4*Ball::r*Ball::r){
                    whiteBall().moveBy(1,0);
                    isIntersect=true;
                }
                else{
                    isIntersect=false;
                }
            }
        }
    }
}

void MainWindow::setBallsDefaultPosition()          //!!!!должно вызываться после инициализации белого шара 0!!!!!
{

    setAngleBallCoord();
    generateBallDefaultPosition();
    auto coords = defaultBallsCoords;		//делаем копию вектора исходных координат (чтоб не портить)

//    for(auto& coord:coords){
//        coord.x*=table->getScale();
//        coord.y*=table->getScale();
//    }
    //std::random_shuffle(coords.begin(), coords.end());		//перемешиваем в случайном порядке
    int n = Balls.size();
    for(int  i=1; i<n; ++i)
    {
        Balls[i]->setCoords(angleBallCoords + coords.back());
        coords.pop_back();
    }


}

void MainWindow::setCalculetedStatusFalse()
{
    for(auto &ball:Balls){
        ball->setCalculatedStatus(false);
    }

}

void MainWindow::calcBallsDistances()
{

    QVector<Ball *> tmp;    //вектор шаров с которыми столкнулся this
    for(auto& currBall:Balls)   //для всех шаров
    {
        if(!currBall->isCalculated() && currBall->isMoving())   //если шар еще не просчитан и движется
        {
            currBall->setCalculatedStatus(true);    //ставим флаг о просчете, что бы не считать второй раз
            for(auto& otherBall:Balls)      //для всех непросчитанных шаров
            {
                if(!otherBall->isCalculated()   //ставим флаг о просчете
                    && currBall->distance(*otherBall) <
                        1.01 * 4 * Ball::r * Ball::r )//сравниваем квадрат дистанции с квадратом диаметра
                {
                    tmp.push_back(otherBall);  //если меньше, кидаем шар в вектор столнувшихся
                }
            }
            if(tmp.size()==1){      //если коснувшихся шаров 1
                if (isFirstTouch())        //ставим метку касания первого шара
                {
                    setFirstTouchStatus(false);
//                    firstTouch=true;
                    setFirstTouchedBall(&Balls[tmp[0]->number]);        //устанавливаем первый коснувшийся шар
                            //это необходимо для логики игра и продолжения хода
                    setTouchStatus(true);
                }
                currBall->collisionTwoBalls(*tmp[0]);       //вызываем метод столкновения двух шаров
                if (!isTouched()){

//                    setFirstTouchedBall(&Balls[tmp[0]->number]); //Устанавливаем первый коснувшийся шар
                    setTouchStatus(true);
                }

            }
            if(tmp.size()==2){  ////если коснувшихся шаров 2
                if (isFirstTouch())
                {
                    setFirstTouchStatus(false);
                    setFirstTouchedBall(&tmp[0]);
                    setTouchStatus(true);
                }
                currBall->collisionThreeBalls(*tmp[0],*tmp[1]);
                if (!isTouched()){
//                    setFirstTouchedBall(&tmp[0]); //Устанавливаем первый коснувшийся шар
                    setTouchStatus(true);
                }
            }
            tmp.clear();        //чистим ветор
        }
    }
}

QVector<Ball *> MainWindow::_calcBallsDistances_TEST()
{
    QVector<Ball *> tmp;
    for(auto& currBall:Balls){
        if(currBall->isCalculated()==false)
        {
            currBall->setCalculatedStatus(true);
            for(auto& otherBall:Balls)
            {
                if(!otherBall->isCalculated()
                        && currBall->distance(*otherBall) < 4 * Ball::r * Ball::r
                        /*&& currBall->isTouch(*otherBall)*/)
                {
                    tmp.push_back(otherBall);
                }
            }
            if(tmp.size()==1){
                currBall->collisionTwoBalls(*tmp[0]);
            }
            if(tmp.size()==2){
                currBall->collisionThreeBalls(*tmp[0],*tmp[1]);
            }
            for(auto ball:tmp){
                if(ball->v0.isNull())
                {
                    ball->setMovingStatus(false);
                }
                if(!ball->v0.isNull())
                {
                    ball->setMovingStatus(true);
                }
            }
            tmp.clear();
        }
    }
    return tmp;
}

void MainWindow::boardCollision()
{
    double d=Ball::r*1*2;        //
    for(auto ball: Balls)
    {
        if (ball->isMoving())
        {
            bool midleArea = ball->y()>height/2-deltaPocket && ball->y()<height/2+deltaPocket;      //в зоне бортовых луз
            if(ball->x()<=Ball::r&&         //LEFT                       
                    ball->y() >=  ball->x()+d&&     //and top left pocket
                    ball->y() <= -ball->x()+height-d&&
                    !midleArea&&        //не в зоне луз
                    ball->v0.x<0)       //чтоб не зациклилось
            {
                ball->v0.x*=-1;
            }

            if(ball->y()<=Ball::r&&     //TOP
                (ball->y() <= ball->x()-d&&
                 ball->y() <= -ball->x()+width-d)&&
                 ball->v0.y<0)
            {
                ball->v0.y*=-1;
            }

            if(ball->x()>=width - Ball::r&&         //RIGHT
                    (ball->y() >= -ball->x()+width+d&&
                     ball->y() <=  ball->x()-width+height-d&&!midleArea)&&
                    ball->v0.x>0)
            {
                    ball->v0.x*=-1;
            }

            if(ball->y()>=height-Ball::r&&     //BOTTOM
                    (ball->y() >= -ball->x()+height+d&&
                     ball->y() >=  ball->x()-width+height+d)
                    &&ball->v0.y>0)
            {
                ball->v0.y*=-1;
            }
        }
    }
}

void MainWindow::checkPocketedBalls()
{
    bool paintedBall=false;
    bool strippedBall=false;
    ///////////////FLAGS//////////////////////
    if (!ballsInPocket.isEmpty()) //выставляем флаги если есть забитые шары
    {
        setNoBallsInPocket(false);
        for(auto ball:ballsInPocket)
        {
            if (*ball==&whiteBall()){
                setWhiteBallInPocket(true);
            }
            if (*ball==&blackBall()){
                setBlackBallInPocket(true);
            }
//            if ((int)(*ball)->getType() != (int)getActivePlayer().getBallType()){  //сравниваем с первым забитым мячом
//                setFoulStatus(true);
//            }
            if((*ball)->getType()==Ball::Type::PAINTED){
                paintedBall=true;
            }
            if((*ball)->getType()==Ball::Type::STRIPPED){
                strippedBall=true;
            }
        }
        if(paintedBall^strippedBall){
            setSameBallInPocketStatus(true);
        }
    }
    else //ни одного шара не забито
    {
        setNoBallsInPocket(true);
    }
    //////////GAME LOGIC///////////
    if(isFirstHit())
    {
        bool foundGameBall=false;
        if(isSameBallInPocket()&&!isFoul())
        {
            getActivePlayer().setBallType((paintedBall) ? Player::BallType::PAINTED : Player::BallType::STRIPPED);
            getWaitingPlayer().setBallType((!paintedBall) ? Player::BallType::PAINTED : Player::BallType::STRIPPED);
            setFirstHitStatus(false);
        }
        else if(isNoBallsInPocked())
        {
            setFirstHitStatus(true);
        }
        if (isBlackInPocket())
        {
            setFoulStatus(true);
            loseGame((*activePlayer));
        }
        else
        {
            if (isWhiteInPocket())
            {
                setFoulStatus(true);
                changeMove();
                setWhiteFoulPosition();
            }
            for(auto ball:ballsInPocket)
            {
                if (!foundGameBall && (*ball)->isGameBall()){
                    foundGameBall=true;
//                    getActivePlayer().setBallType((Player::BallType)(*ball)->getType());
                    setFirstHitStatus(false);
                    break;
                }
            }
            if(firstTouchedBall==nullptr)
            {
                setNoBallTouchStatus(true);
                setFoulStatus(true);
            }
            else if(getFirstTouchedBall().getType()==Ball::Type::BLACK){
                setFoulStatus(true);
            }
            else{
                setNoBallTouchStatus(false);
            }
            /////////////LOGIC for FIRST shots
            if (isBlackInPocket()){
                    loseGame((*activePlayer));
            }
            else //если черный не забит
            {
                if (isWhiteInPocket())
                {
                    setFoulStatus(true);
                    changeMove();
                    setWhiteFoulPosition();
                }
                else{
                    if(isFoul())
                    {
                       changeMove();
                       setWhiteFoulPosition();
                    }
                    else if (isNoBallsInPocked())
                    {
                        changeMove();
                    }
                }
            }
            goOn();
        }

    } //endif first ball
    else  //firstBall==false
    {
        if(firstTouchedBall)
        {
            setNoBallTouchStatus(false);
            if((int)((*firstTouchedBall)->getType())!=(int)(getActivePlayer().getBallType()))
            {
                setFoulStatus(true);
            }
            else{
                setFoulStatus(false);
            }
        }
        else{
            setFoulStatus(true);
            setNoBallTouchStatus(true);
        }
        /////////////LOGIC for not firstd shots
        if (isBlackInPocket()){
            if((*activePlayer)->isLastBall() && !isFoul()){
             winGame((*activePlayer));  //если забит черный шар и он был последний и нет фола, то побеждает актив плэйер
            }
            else
            {
                loseGame((*activePlayer));
            }
        }
        else //если черный не забит
        {
            if (isWhiteInPocket())
            {
                setFoulStatus(true);
                changeMove();
                setWhiteFoulPosition();
            }
            else{
                if(isFoul())
                {
                   changeMove();
                   setWhiteFoulPosition();
                } else if(isNoBallsInPocked())
                {
                    changeMove();
                }
            }
            goOn();
        }
    } //end else 
}
//void MainWindow::boardCollision()
//{
//    double d=Ball::r*scale;
//    for(auto ball: Balls)
//    {
//        if(ball->isMoving() && (ball->x()<=0+Ball::r && ball->y() < ball->x()-d || ball->x()>=this->width-Ball::r))
//        {
//            ball->v0.x*=-1;
//        }
//        if(ball->isMoving()&&(ball->y()<=0+Ball::r||ball->y()>=this->height-Ball::r))
//        {
//            ball->v0.y*=-1;
//        }
//    }
//}

void MainWindow::moveBalls()
{
    ballsMoving=false;
    for(auto& ball:Balls)
    {
        if(ball->isMoving())
        {
            setBallsInMoving(true);
            ball->move();
        }
    }

}

void MainWindow::pocketChech()
{
    double d=Ball::r*2;
    for(auto& ball:Balls)
    {
        double k=1;
        double delta = 3.;
        if(ball->isMoving())
        {
            if (
                ball->y() < (-ball->x()+d)*k +delta||       //top left
                ball->y() <  (ball->x()-width+d)*k+delta ||         //top right
                ball->y() >  (ball->x()+height-d )*k-delta||        //bottom right
                ball->y() > (-ball->x()+width+height-d)*k-delta     //bottom left
                    ||( (ball->x() < 0+delta || ball->x() > width-delta) &&
                        (ball->y() < height/2+pocketSize/2*k &&
                         ball->y() > height/2-pocketSize/2*k))
                )
            {
                ballsInPocket.push_back(&ball);
                ball->setActiveStatus(false);
                QPointF posBall;

                if (!isPlayerBallTypeDefined()){
                    if (ball->isGameBall()){
                        getActivePlayer().setBallType((Player::BallType)ball->getType());
                        getWaitingPlayer().setBallType((Player::BallType)((ball->getType()==Ball::Type::PAINTED)?
                                                           Ball::Type::STRIPPED :
                                                           Ball::Type::PAINTED));
                        setPlayerBallTypeDefinedStatus(true);
                        getActivePlayer().raiseBallCount(1);
                        posBall=this->getActivePlayer().getNextBallShelfPoint();
                        ball->setPos(posBall+getActivePlayer().mapToItem(table,QPointF(0,0)));
                    }
                    if(ball->getType()==Ball::Type::BLACK)
                    {

                        posBall=table->getBlackBallWaitingPos();
                        ball->setPos(posBall);

                    }
                    if(ball->getType()==Ball::Type::WHITE)
                    {
                        posBall=table->getWhiteBallWaitingPos();
                        ball->setPos(posBall);
                    }

                }
                else
                {

                    if ((int)ball->getType()==(int)getActivePlayer().getBallType())
                    {
                        getActivePlayer().raiseBallCount(1);
                        posBall=this->getActivePlayer().getNextBallShelfPoint();
                        ball->setPos(posBall+getActivePlayer().mapToItem(table,QPointF(0,0)));
                    }
                    if ((int)ball->getType()==(int)getWaitingPlayer().getBallType())
                    {
                        getWaitingPlayer().raiseBallCount(1);
                        posBall=this->getWaitingPlayer().getNextBallShelfPoint();
                        ball->setPos(posBall+getWaitingPlayer().mapToItem(table,QPointF(0,0)));
                    }
                    if(ball->getType()==Ball::Type::BLACK)
                    {
                        if (getActivePlayer().isLastBall()){
                            getActivePlayer().raiseBallCount(1);
                            posBall=this->getActivePlayer().getNextBallShelfPoint();
                            ball->setPos(posBall+getActivePlayer().mapToItem(table,QPointF(0,0)));
                        }
                        else{
                            posBall=table->getBlackBallWaitingPos();
                            ball->setPos(posBall);
                        }
                    }
                    if(ball->getType()==Ball::Type::WHITE)
                    {

                            posBall=table->getWhiteBallWaitingPos();
                            ball->setPos(posBall);

                    }
//                    if (getActivePlayer().getBallType()==Player::BallType::NO_TYPE)
//                    {
//                        getActivePlayer().raiseBallCount(1);
//                        posBall=this->getActivePlayer().getNextBallShelfPoint();
//                        ball->setPos(posBall+getActivePlayer().mapToItem(table,QPointF(0,0)));
//                    }
                }

            }
        }
    }
}

//void f_coord(Coord curr, double r, QSet<Coord> &setCoord, int &i);
void MainWindow::generateBallDefaultPosition()
{
    double r=Ball::r*1.08;
    QVector<Coord> defaultCoord;

    //int sum=0;

    defaultBallsCoords    <<Coord(0,0)
               <<Coord(-r,-sqrt(3)*r)<<Coord(r,-sqrt(3)*r)
            <<Coord(-2*r,-2*sqrt(3)*r)<<Coord(0,-2*sqrt(3)*r)<<Coord(2*r,-2*sqrt(3)*r)

        <<Coord(-3*r,-3*sqrt(3)*r)<<Coord(-r,-3*sqrt(3)*r)<<Coord(r,-3*sqrt(3)*r)<<Coord(3*r,-3*sqrt(3)*r)
     <<Coord(-4*r,-4*sqrt(3)*r)<<Coord(-2*r,-4*sqrt(3)*r)<<Coord(0,-4*sqrt(3)*r)<<Coord(2*r,-4*sqrt(3)*r)<<Coord(4*r,-4*sqrt(3)*r);
//    f_coord(Coord(0,0), r, setCoord, i);

    qDebug()<<"Coords compleet";

}
//void f_coord(Coord curr, double r, QSet<Coord> &setCoord, int &i)
//{
//    Coord right;
//    Coord left;
//    if  (i==16) return;
//    else
//    {
//         right=curr+Coord(r,-sqrt(3)*r);
//         left=curr+Coord(-r,-sqrt(3)*r);

//         if(setCoord.insert(right)!=setCoord.end()){
//             ++i;
//             f_coord(right, r, setCoord, i);
//         }

//         if(setCoord.insert(left)!=setCoord.end()){
//             ++i;
//             f_coord(left, r, setCoord, i);
//         }
//    }
//    return;
//}
void MainWindow::_moveBallsTest()
{

    for(auto& ball:Balls){
        if(ball->isMoving()){
            ball->_moveTest();
            scene->update();
        }
    }
}


void MainWindow::pitch()
{

    for(int i =0;i<40;++i)
    {
        setCalculetedStatusFalse();     //высталяем статус "просчитан" в ложь для всех шаров
        pocketChech();              //проверяем падение в лузу
        boardCollision();             //проверяем столкновение с бортом
        calcBallsDistances();            //провереряем дистанцию между шарами
        moveBalls();              //продвегаем все находящиеся в движении шары на одну итрецию
    }
    scene->update();    //отрисовываем сцену
    if (!ballsInMoving())       //Обработка завершения движения шаров
    {
        timer->stop();      //останавливаем таймер
        checkPocketedBalls();   //проверяем забитые шары
        if (isGameActive()){
            setCuePosition();   //устанавливаем кий на белый шар
            cue->show();
        }
    }
}

void MainWindow::_setSpeedForAllBall()      //////!!TEST!!/////////
{
    srand(time(0));
    for(auto ball:Balls)
    {
        int neg=-1;
        if(rand()%2==1){
            neg=1;
        }
        ball->v0.x=neg*rand()%150;
        if(rand()%2==1){
            neg=-1;
        }
        ball->v0.y=neg*rand()%150;
    }
}


///////////!!!!!!!//////////////////////////////////////////////////////////////////////////////////////
void MainWindow::setTestPosition()
{
//    Balls[0]->setCoords(70,70);
//    Balls[1]->setCoords(50,50);


    Balls[0]->setCoords(width - 70,70);
    Balls[1]->setCoords(width - 50,50);
    Balls[0]->setCoords(width - 70,height - 70);
    Balls[1]->setCoords(width - 50,height - 50);
    Balls[0]->setCoords(70,height - 70);
    Balls[1]->setCoords(50,height - 50);
//    Balls[0]->setCoords(13,height - 90);
//    Balls[1]->setCoords(13,height - 50);

    Balls[0]->setCoords(width -60,height/2);
    Balls[1]->setCoords(width -20,height/2);

    Balls[0]->setCoords(60,height/2);
    Balls[1]->setCoords(20,height/2);
    Balls[9]->setCoords(width -20,height/2);


//    Balls[2]->setCoords(350,280);
//    Balls[2]->setV(-100,50);
}

void MainWindow::clearScene()
{
    if(!timer->isActive()){
        timer->stop();
    }

    scene->clear();


}

void MainWindow::clearTable()
{
    timer->stop();
    for(auto ball:Balls){
        scene->removeItem(ball);
//        ball->setParent(0);
        delete ball;

//        ball->hide();
    }
    setBallsInMoving(false);
//    if(table){
//        scene->removeItem(table);
//        delete table;
//    }

    Balls.clear();
    if (cue)
    {
        cue->hide();
    }

    scene->update();
    setGameActiveStatus(false);

}

void MainWindow::setTestObjects()
{
    Ball * testBall = new Ball(Coord(450,450), 20, Qt::white, Ball::Type::PAINTED,table->getScale(),table);
    scene->addItem(testBall);
}

void MainWindow::_setBalls_TEST()
{
    Balls.clear();
    Balls.emplace_back(new Ball(Coord(), 0, Qt::white, Ball::Type::WHITE,table->getScale(),table));

    Balls.emplace_back(new Ball(Coord(), 1, Qt::yellow, Ball::Type::PAINTED,table->getScale(),table));
    Balls.emplace_back(new Ball(Coord(), 2, Qt::blue, Ball::Type::PAINTED,table->getScale(),table));
//    Balls.emplace_back(new Ball(Coord(), 3, Qt::red, Ball::Type::PAINTED,table->getScale(),table));
//    Balls.emplace_back(new Ball(Coord(), 4, QColor(QRgb(0x6600cc)), Ball::Type::PAINTED,table->getScale(),table));
//    Balls.emplace_back(new Ball(Coord(), 5, QColor(QRgb(0xfa9a00)), Ball::Type::PAINTED,table->getScale(),table));
//    Balls.emplace_back(new Ball(Coord(), 6, Qt::green, Ball::Type::PAINTED,table->getScale(),table));
//    Balls.emplace_back(new Ball(Coord(), 7, QColor(QRgb(0x331a00)), Ball::Type::PAINTED,table->getScale(),table));

    Balls.emplace_back(new Ball(Coord(), 8, Qt::black, Ball::Type::BLACK,table->getScale(),table));

    Balls.emplace_back(new Ball(Coord(), 9, Qt::yellow, Ball::Type::STRIPPED,table->getScale(),table));
    Balls.emplace_back(new Ball(Coord(), 10, Qt::blue, Ball::Type::STRIPPED,table->getScale(),table));
//    Balls.emplace_back(new Ball(Coord(), 11, Qt::red, Ball::Type::STRIPPED,table->getScale(),table));
//    Balls.emplace_back(new Ball(Coord(), 12, QColor(QRgb(0x6600cc)), Ball::Type::STRIPPED,table->getScale(),table));
//    Balls.emplace_back(new Ball(Coord(), 13, QColor(QRgb(0xfa9a00)), Ball::Type::STRIPPED,table->getScale(),table));
//    Balls.emplace_back(new Ball(Coord(), 14, Qt::green, Ball::Type::STRIPPED,table->getScale(),table));
//    Balls.emplace_back(new Ball(Coord(), 15, QColor(QRgb(0x331a00)), Ball::Type::STRIPPED,table->getScale(),table));

    setWhiteBallPosition();
    setBallsDefaultPosition();      //set balls coordinates in random order
//    setTestPosition();          //!!!!!!!!TEST!!!!

   for(auto &ball:Balls)
   {
       scene->addItem(ball);
       ball->setPos(ball->x0, ball->y0);
   }
//        _setSpeedForAllBall();      //!!!TEST!!!!
}

void MainWindow::on_NewGameBtn_clicked()
{
        clearTable();
        setNewGame();
        scene->update();
        setGameActiveStatus(true);
}


void MainWindow::on_ClearBtn_clicked()
{

    clearTable();
    setGameActiveStatus(false);
//    scene->update();
//    setStartView();

//    clearScene();
//    Balls.clear();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(!ballsInMoving()&&cue&&isGameActive())
    {
        qDebug()<<"mousePressEvent";
//        QPointF pTo =  table->mapToParent(event->pos());
//        QPointF pFrom =  table->mapFromParent(event->pos());
//        QPointF eventPoint = event->pos()-QPointF(20,20); //////////FIXIT!!!!!!!!!!!!
//        QPointF eventPoint = pTo;
//        qDebug()<<pTo<<pFrom<<event->pos();

//        setCueRotation(event->pos()-QPointF(w->TABLE_OFFSET_X,w->TABLE_OFFSET_X));
        cue->setCuePower(0);
        cue->cueTimer->start(10);
        getActivePlayer().setPreparingKickStatus(true);
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{

    qDebug()<<"mouseMoveEvent";
}

void MainWindow::mouseReleaseEvent(QMouseEvent *)
{
    if(isGameActive()){
        if(!ballsInMoving())
        {
            qDebug()<<"mouseReleaseEvent";
            cue->cueTimer->stop();
            setWhiteBallSpeed(cue->alpha,cue->power);
            whiteBall().setActiveStatus(true);
            qDebug()<<cue->alpha<<cue->power;
            whiteBall().setMovingStatus(true);
            setDeltaVDefault();
            timer->start(1000/60);
            getActivePlayer().setPreparingKickStatus(false);
            cue->hide();

        }
    }
}
void MainWindow::setCueRotation(QPointF eventPoint)
{
//    QPointF eventPoint = eventPointRaw-QPointF(20,20);
    QPointF whiteBallPoint = whiteBall().pos();
    QPointF relativePoint = eventPoint-whiteBallPoint;
    //qDebug()<<relativePoint;
    double dist = sqrt((relativePoint.x())*(relativePoint.x())+
                           (relativePoint.y())*(relativePoint.y()));
    cue->alpha = acos(relativePoint.x()/dist);
    cue->alpha = relativePoint.y() > 0 ? cue->alpha: 2*M_PI-cue->alpha;
    QPointF cueRotationPoint = whiteBall().pos()-cue->pos();
    cue->setTransformOriginPoint(cueRotationPoint);
    cue->setRotation(cue->alpha*180/M_PI);
    scene->update();
}

void MainWindow::setPockets()
{
    pocketSize = Ball::r*2*1.44;
    QPointF tableOffset;
    if (iSii()){
        tableOffset = QPointF(TABLE_OFFSET_X*iiScale,TABLE_OFFSET_Y*iiScale);
    }
    else{
        tableOffset = QPointF(TABLE_OFFSET_X,TABLE_OFFSET_Y);
    }

    double d = 2*Ball::r;
    pockets.clear();
    pockets.push_back(new Pocket(QPointF(0,0),0,Ball::r,1.44,table));

    scene->addItem(pockets[0]);
    pockets[0]->setPos(QPointF(0,d)+tableOffset);
    pockets[0]->setRotation(-45);

    pockets.push_back(new Pocket(QPointF(0,0),0,Ball::r,1.44,table));
    scene->addItem(pockets[1]);
    pockets[1]->setPos(QPointF(width-d,0)+tableOffset);
    pockets[1]->setRotation(45);


    pockets.push_back(new Pocket(QPointF(0,0),0,Ball::r,1.44,table));
    scene->addItem(pockets[2]);
    pockets[2]->setPos(QPointF(width,height-d)+tableOffset);
    pockets[2]->setRotation(135);

    pockets.push_back(new Pocket(QPointF(0,0),0,Ball::r,1.44,table));
    scene->addItem(pockets[3]);
    pockets[3]->setPos(QPointF(d,height)+tableOffset);
    pockets[3]->setRotation(225);

    pockets.push_back(new Pocket(QPointF(0,0),0,Ball::r,1.44,table));
    scene->addItem(pockets[4]);
    pockets[4]->setPos(QPointF(0,height/2+pocketSize/2)+tableOffset);
    pockets[4]->setRotation(-90);

    pockets.push_back(new Pocket(QPointF(0,0),0,Ball::r,1.44,table));
    scene->addItem(pockets[5]);
    pockets[5]->setPos(QPointF(width,height/2-pocketSize/2)+tableOffset);
    pockets[5]->setRotation(90);

}

void MainWindow::setPlayers()
{
    if(player1){
        delete player1;
    }
    player1 = new Player("First Player",Ball::r,table);
    scene->addItem(player1);
    player1->setPos(firstPlayerPos);

    if(player2)
    {
        delete player2;
    }
    player2 = new Player("Second Player",Ball::r,table);
    scene->addItem(player2);
    player2->setPos(secondPlayerPos);
    activePlayer=(rand()%2==1)?&player1:&player2;
    setPlayersActiveStatus();

}

void MainWindow::setPlayersActiveStatus()
{
    getActivePlayer().setActiveStatus(true);
    getWaitingPlayer().setActiveStatus(false);

}

void MainWindow::setFoulStatus(bool foulStatus)
{
    foul=foulStatus;
}

void MainWindow::setWhiteBallInPocket(bool whiteStatus)
{
    whiteBallInPocket=whiteStatus;
}

void MainWindow::setBlackBallInPocket(bool blackStatus)
{
    blackBallInPocket=blackStatus;
}

void MainWindow::setNoBallsInPocket(bool noBallStatus)
{
    noBallsInPocket=noBallStatus;
}

void MainWindow::setTouchStatus(bool touchedStatus)
{
    ballsTouch=touchedStatus;
}

void MainWindow::setFirstHitStatus(bool hitStatus)
{
    firstHit=hitStatus;
}

void MainWindow::setSameBallInPocketStatus(bool sameBallStatus)
{
    sameBallInPocket=sameBallStatus;
}

void MainWindow::setDeltaVDefault()
{
    deltaV=deltaVDefault;
}

void MainWindow::setFirstTouchedBall(Ball ** ball)
{
    firstTouchedBall=ball;
    setTouchStatus(true);
}

void MainWindow::setNoBallTouchStatus(bool status)
{
    noBallTouch=status;

}

void MainWindow::setBallsInMoving(bool status)
{
    ballsMoving=status;
}

void MainWindow::setPlayerBallTypeDefinedStatus(bool status)
{
    playerBallTypeDefined=status;
}

void MainWindow::setFirstTouchStatus(bool status)
{
    firstTouch=status;
}

bool MainWindow::ballsInMoving()
{
    return ballsMoving;
}

void MainWindow::changeMove()
{
    activePlayer = (activePlayer==&(player1))? &player2: &player1;
    setPlayersActiveStatus();
}

void MainWindow::goOn()
{
    setFirstTouchedBall(nullptr);
    setWhiteBallInPocket(false);
    setBlackBallInPocket(false);
    setNoBallsInPocket(true);
    setFoulStatus(false);
    setNoBallTouchStatus(true);
    setBallsInMoving(false);
    setGameActiveStatus(true);
    setFirstTouchStatus(true);
    ballsInPocket.clear();


}

Ball &MainWindow::getFirstTouchedBall()
{
    return **firstTouchedBall;
}

void MainWindow::on_stopBalls_clicked()
{
    for(auto ball:w->Balls)
    {
        ball->setSpeed(0,0);
    }
}


void MainWindow::on_IIMoveBtn_clicked()
{
//    IIMove();

}


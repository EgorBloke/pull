


#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H
#include <QGraphicsView>
class MyGraphicsView: public QGraphicsView{
public:

    MyGraphicsView(QWidget *parent = nullptr);



    // QPaintDevice interface


    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

friend class MyGraphicsView;

    // QPaintDevice interface

};

#endif // MYGRAPHICSVIEW_H





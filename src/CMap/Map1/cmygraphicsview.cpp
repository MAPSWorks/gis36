#include "cmygraphicsview.h"

CMyGraphicsView::CMyGraphicsView(QWidget *parent) :
    QGraphicsView(parent)
{
    this->setMouseTracking(true);

    scene = new QGraphicsScene(this);
    this->setScene(scene);

    QBrush greenBrush (Qt::green);//������� �������
    QBrush blueBrush (Qt::blue);//������� �������
    QPen blpen (Qt::black);//������ �����
    QPen whitepen (Qt::white);//����� �����
    whitepen.setWidth(1);
    blpen.setWidth(1.5);//������� ������� ����� ����� ����� � ������ ��������������


    QPolygonF polygon,polyg;
    polygon << QPointF(0, 0) << QPointF(100, 0) << QPointF(50, 50) ;
    polyg << QPointF(0,10)<<QPointF(100,10)<< QPointF(50,-50);// �������� 2 �������� ��������� � ������� polygon, polyg


    poly1 = scene->addPolygon (polygon,whitepen,greenBrush);//���������� �������� �� �����
    poly2 = scene-> addPolygon (polyg,blpen,blueBrush);//--||--
    //poly1->setFlag(QGraphicsItem::ItemIsMovable);
    poly1->setToolTip("forest");//����������� ���������, ������� ������� ������� forest ��� ��������� ������� �� ������ poly1

}

void CMyGraphicsView::mouseMoveEvent(QMouseEvent *event){
    QString s_pos = QString::number(event->x()) +
                    " " +
                    QString::number(event->y());

    this->setToolTip(s_pos);// ��� �������� �� ����� ��� �������� poly1 ���������� ���������� ������� �� �����
}


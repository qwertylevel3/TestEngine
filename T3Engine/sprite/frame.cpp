#include "frame.h"
#include"T3Engine/render/rendermodule.h"
#include"T3Engine/manager/picturemanager.h"

Frame::Frame(const QString& pictureName, const QRectF &fp,
             const int w,const int h)
{
    this->pictureName=pictureName;
    picturePoint=PictureManager::instance()->getPicture(pictureName);
    if(!picturePoint)
    {
        qDebug()<<"picturePoint"<<pictureName<<" is empty"<<endl;
    }
    framePosition=fp;
    width=float(w)/200;
    height=float(h)/200;
    qDebug()<<width<<" "<<height<<endl;
}


Frame::~Frame()
{
}

void Frame::addRect(const QRectF &r)
{
    QRectF temp(r);
    rects.push_back(temp);
}

void Frame::addRect(float x, float y, float dx, float dy)
{
    QRectF temp(x,y,width,height);
    rects.push_back(temp);
}

void Frame::draw(float x, float y,float z,float zoomX,float zoomY,
                 bool mir, float angle, float ax, float ay, float az)
{

    picturePoint->setTexturePosition(framePosition.x()/picturePoint->getImageWidth(),
                          framePosition.y()/picturePoint->getImageHeight(),
                          framePosition.width()/picturePoint->getImageWidth(),
                          framePosition.height()/picturePoint->getImageHeight());

    //qDebug()<<framePosition.x()<<endl;
    //qDebug()<<framePosition.y()<<endl;
    //qDebug()<<framePosition.width()/p->getImageWidth()<<endl;
    //qDebug()<<framePosition.height()/p->getImageHeight()<<endl;

    picturePoint->setCoordinate(x,y,z);

    picturePoint->setZoomX(zoomX);
    picturePoint->setZoomY(zoomY);
    picturePoint->mirror(mir);
    picturePoint->rotate(angle,ax,ay,az);
    picturePoint->setWidth(width);
    picturePoint->setHeight(height);
    picturePoint->draw();
}

void Frame::drawRect()
{
//    Picture* p=PictureManager::instance()->getPicture(picture);
//    if(!p)
//    {
//        qDebug()<<"can not get picture point:"<<picture<<endl;
//        return;
//    }
//
//	Picture* r=PictureManager::instance()->getPicture("rect");
//	if(!r)
//	{
//		qDebug()<<"can not get picture point:"<<"rect"<<endl;
//		return;
//	}
//
//	float px=framePosition.x()/p->getImageWidth();
//	float py=framePosition.y()/p->getImageHeight();
//
//	for(int i=0;i<rects.size();i++)
//	{
//		p->setTexturePosition(0,0,1,1);
//
//		if(!mir)
//		{
//			r->setCoordinate(x+rects[i].x()*p->getImageWidth(),
//			                 y+rects[i].y()*p->getImageHeight(),z);
//		}
//		else
//		{
//			r->setCoordinate(x+mrects[i].x()*p->getImageWidth(),
//			                 y+mrects[i].y()*p->getImageHeight(),z);
//		}
//
//		p->setZoom(zoom);
//		p->rotate(angle,ax,ay,az);
//		p->draw();
//	}
}


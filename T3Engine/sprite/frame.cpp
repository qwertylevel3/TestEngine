#include "frame.h"
#include"T3Engine/render/rendermodule.h"
#include"T3Engine/manager/picturemanager.h"

Frame::Frame(const QString& pictureName, const QRectF &fp)
{
    picture=pictureName;
    framePosition=fp;
}


Frame::~Frame()
{
}

void Frame::addRect(const QRectF &r)
{
//    QRectF temp(r);
//    rects.push_back(temp);
//
//    QRectF mtemp(pixmap.width()-x-width,
//                 y,
//                 width,
//                 height);
//    mrects.push_back(mtemp);
}

void Frame::addRect(float x, float y, float dx, float dy)
{
//    QRectF temp(x,y,width,height);
//    rects.push_back(temp);
//
//    QRectF mtemp(pixmap.width()-x-width,
//                 y,
//                 width,
//                 height);
//      mrects.push_back(mtemp);
}

void Frame::draw(float x, float y,float z,float zoomX,float zoomY,
                 bool mir, float angle, float ax, float ay, float az)
{

    Picture* p=PictureManager::instance()->getPicture(picture);
    if(!p)
    {
        qDebug()<<"can not get picture point:"<<picture<<endl;
        return;
    }
    p->setTexturePosition(framePosition.x()/p->getImageWidth(),
                          framePosition.y()/p->getImageHeight(),
                          framePosition.width()/p->getImageWidth(),
                          framePosition.height()/p->getImageHeight());

    //qDebug()<<framePosition.x()<<endl;
    //qDebug()<<framePosition.y()<<endl;
    //qDebug()<<framePosition.width()/p->getImageWidth()<<endl;
    //qDebug()<<framePosition.height()/p->getImageHeight()<<endl;

    p->setCoordinate(x,y,z);

    p->setZoomX(zoomX);
    p->setZoomY(zoomY);
    p->mirror(mir);
    p->rotate(angle,ax,ay,az);
    p->draw();
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


#include "action.h"

Action::Action()
{
    frameDelay=1;
    frameTotal=0;
    isRepeat=false;
    currFrame=0;
    frameClock=0;

    repeatStart=0;
    repeatOver=0;

}

Action::~Action()
{

}

void Action::start()
{
    currFrame=repeatStart;
}
//update,return the state:0,over;1,busy
int Action::update()
{
    if(frameClock++==frameDelay)
    {
        frameClock=0;
        if(isRepeat)
        {
            currFrame=(++currFrame>repeatOver?0:currFrame);
            return 1;
        }
        else
        {
            if(++currFrame>repeatOver)
            {
                currFrame=repeatStart;
                return 0;
            }
        }
    }
    return 1;
}

void Action::end()
{

}


void Action::draw(float x, float y, float z,float zoom, bool mir
        ,float angle,float ax,float ay,float az)
{
    frameBox[currFrame]->draw(x,y,z,zoom,mir,angle,ax,ay,az);
//    //绘制碰撞矩形
//    if(showRect)
//    {
//        painter->setOpacity(0.5);
//        if(oritation==-1)
//        {
//            painter->setBrush(QBrush(Qt::blue,Qt::SolidPattern));
//            for(int i=0;i<frameBox[currFrame].mrects.size();i++)
//            {
//                double x,y,w,h;
//                x=sprite->pos().x()+frameBox[currFrame].mrects[i].x();
//                y=sprite->pos().y()+frameBox[currFrame].mrects[i].y();
//                w=frameBox[currFrame].mrects[i].width();
//                h=frameBox[currFrame].mrects[i].height();
//                painter->drawRect(x,y,w,h);
//            }
//        }
//        else if(oritation==1)
//        {
//            painter->setBrush(QBrush(Qt::blue,Qt::SolidPattern));
//            for(int i=0;i<frameBox[currFrame].rects.size();i++)
//            {
//                double x,y,w,h;
//                x=sprite->pos().x()+frameBox[currFrame].rects[i].x();
//                y=sprite->pos().y()+frameBox[currFrame].rects[i].y();
//                w=frameBox[currFrame].rects[i].width();
//                h=frameBox[currFrame].rects[i].height();
//                painter->drawRect(x,y,w,h);
//            }
//        }
    //    }
}

void Action::drawRect()
{
    frameBox[currFrame]->drawRect();
}


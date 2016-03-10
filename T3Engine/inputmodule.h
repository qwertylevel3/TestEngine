#ifndef INPUTMODULE_H
#define INPUTMODULE_H
#include"singleton.h"

class Entity;
#include"stable.h"
//处理键盘映射
class InputModule:public QObject,public Singleton<InputModule>
{
    Q_OBJECT
public:
    enum Command{enter,up,down,left,right,A_C,B_C,C_C,D_C,E_C,F_C};

    InputModule();
    ~InputModule();
    void input(int key);
    void setCommand(int key,Command c){keyMap[key]=c;}
    Command getCommand();
    Command popCommand();
    void setEntity(Entity* e);
public slots:
    void keyPressEvent(QKeyEvent* e);
    void keyReleaseEvent(QKeyEvent* e);
protected:
    void shutdownAllCommand();
    bool getInput;
    QMap<int,Command> keyMap;//键盘映射表
    QMap<Command,bool> runningList;//正在按下的集合
    QStack<Command> commandStack;//命令栈
    Entity* entity;
};

#endif // INPUTMODULE_H

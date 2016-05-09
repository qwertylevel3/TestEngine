#ifndef CHARACTER_H
#define CHARACTER_H

#include"skill.h"
#include"entity.h"
#include"orientation.h"
#include"ai.h"
#include"ainode.h"

class Character:public Entity
{
public:
    enum TYPE{PLAYER,ENEMY,FRIEND};

    Character(const QString& spriteName);
    virtual ~Character();

    void draw();
    void update();
    Character* clone();

    void startCommand(InputModule::Command c);
    void endCommand(InputModule::Command c);

    int getHP() const;
    void setHP(int value);

    int getMP() const;
    void setMP(int value);

    int getCurrentHP() const;
    void setCurrentHP(int value);

    int getCurrentMP() const;
    void setCurrentMP(int value);

    float getSpeed() const;
    void setSpeed(float value);

    Orientation::ORIENTATION getOrientation() const;
    void setMoveOrientation(const Orientation::ORIENTATION &value);
    void setReadyOrientation(const Orientation::ORIENTATION &value);

    int getHeartRate() const;
    void setHeartRate(int value);

    TYPE getType() const;
    QString typeToString(const TYPE &value);
    void setType(const TYPE &value);
    void setType(const QString& value);

    int getFocusIndex() const;
    void setFocusIndex(int value);

    void getDamage(float damage);
    void dead();
    bool getInvincible() const;
    void setInvincible(bool value);

    void clearHeartAlarm();
    bool isHeartAlarm();
    void initAI();
    void initClock();
    void init();
    AINode *getAi() const;
    void setAi(AINode *value);

    QVector2D getViewField() const;
    void setViewField(const QVector2D &value);

    QVector2D getAlarmField() const;
    void setAlarmField(const QVector2D &value);

    InputModule::Command getCurrentCommand() const;
    void setCurrentCommand(const InputModule::Command &value);

    bool isRunning();
    bool isMovingUp();
    bool isMovingDown();
    bool isMovingLeft();
    bool isMovingRight();
    void stopMoving();

    QString getCurrentScene() const;
    void setCurrentScene(const QString &value);

protected:
    void initSkill();
    void initParamater();
    void runSkill();
    void runAI();

    void startUp();
    void startDown();
    void startLeft();
    void startRight();
    void startA_C();
    void startB_C();

    void endUp();
    void endDown();
    void endLeft();
    void endRight();
    void endA_C();
    void endB_C();

    int HP;
    int MP;
    int currentHP;
    int currentMP;
    float speed;
    bool invincible;

    Orientation::ORIENTATION orientation;
    Orientation::ORIENTATION lastOrientation;
    QMap<QString,Skill*> skillBox;
//    QList<AI*> AIList;

    int heartId;
    int heartRate;

    TYPE type;

    int focusIndex;

    void drawField(QVector2D r);
    QVector2D viewField;
    QVector2D alarmField;

    AINode* ai;
    InputModule::Command currentCommand;

    //the scene that character location now
    QString currentScene;

};

#endif // CHARACTER_H

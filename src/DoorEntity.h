#ifndef DOORENTITY_H
#define DOORENTITY_H

#include "sfml_game/SpriteEntity.h"

enum doorEnum
{
  DoorStandard_0,
  DoorStandard_1,
  DoorStandard_2,
  DoorStandard_3,
  DoorStandard_4,
  DoorBoss,
  DoorChallenge,
  DoorExit
};

class DoorEntity : public SpriteEntity
{
  public:
    DoorEntity(int direction);
    virtual void animate(float delay);
    void render(sf::RenderTarget* app);
    void renderDoors(sf::RenderTarget* app);

    void setOpen(bool open);
    void setDoorType(doorEnum doorType);
    void closeDoor();
    void openDoor();

  private:
    int direction;
    bool isOpen;
    float timer;
    doorEnum doorType;
};
#endif // DOORENTITY_H

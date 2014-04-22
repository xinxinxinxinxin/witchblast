#include "ArtefactDescriptionEntity.h"
#include "Constants.h"
#include "sfml_game/ImageManager.h"
#include "WitchBlastGame.h"
#include "StaticTextEntity.h"
#include "Items.h"

ArtefactDescriptionEntity::ArtefactDescriptionEntity(enumItemType itemType, WitchBlastGame* parent)
      : SpriteEntity (ImageManager::getImageManager()->getImage(IMAGE_ITEMS_EQUIP), 0, 0, ITEM_WIDTH, ITEM_HEIGHT)
{
  this->setLifetime(6.0f);

  this->setFrame(itemType - itemMagicianHat);
  this->setType(ENTITY_ARTIFACT_DESCRIPTION);

  float x0 = OFFSET_X + MAP_WIDTH * TILE_WIDTH * 0.5f - ARTEFACT_RECT_WIDTH * 0.5f;

  rectangle.setSize(sf::Vector2f(ARTEFACT_RECT_WIDTH, ARTEFACT_RECT_HEIGHT));
  rectangle.setPosition(sf::Vector2f(x0, ARTEFACT_POS_Y));
  rectangle.setFillColor(sf::Color(20, 20, 70, 180));

  rectangleBorder.setSize(sf::Vector2f(ARTEFACT_RECT_WIDTH + ARTEFACT_BORDER * 2.0f,
                                      ARTEFACT_RECT_HEIGHT + ARTEFACT_BORDER * 2.0f));
  rectangleBorder.setPosition(sf::Vector2f(x0 - ARTEFACT_BORDER, ARTEFACT_POS_Y - ARTEFACT_BORDER));
  rectangleBorder.setFillColor(sf::Color(255, 255, 255, 180));

  this->parent = parent;

  this->x = x0 + 50.0f;
  this->y = 500.0f;
  sprite.setScale(3.5f, 3.5f);

  z = 5000.0f;

  /*switch (itemType)
  {
    case (ItemEntity::itemMagicianHat):
      artefactName = "Enchanter Hat"; artefactDescription = "Increases fire rate"; break;
    case (ItemEntity::itemLeatherBoots):
      artefactName = "Leather Boots"; artefactDescription = "Increases speed"; break;
    case (ItemEntity::itemBookDualShots):
      artefactName = "Spell : Dual Bolts"; artefactDescription = "Shoots two bolts"; break;
    case (ItemEntity::itemConcentrationAmulet):
      artefactName = "Concentration Amulet"; artefactDescription = "Increases fire range"; break;
    case (ItemEntity::itemBossKey):
      artefactName = "Boss Key"; artefactDescription = "Open the boss gate"; break;
    case (ItemEntity::itemVibrationGloves):
      artefactName = "Vibration Gloves"; artefactDescription = "Vibrations + slighty increases fire rate"; break;
    case (ItemEntity::itemMahoganyStaff):
      artefactName = "Mahogany Staff"; artefactDescription = "Increases bolt's speed and damages"; break;
    case (ItemEntity::itemFairy):
      artefactName = "Fairy"; artefactDescription = "Help you in the dungeon"; break;
    case (ItemEntity::itemLeatherBelt):
      artefactName = "Leather Belt"; artefactDescription = "Increases fire rate"; break;
    case (ItemEntity::itemBloodSnake):
      artefactName = "Blood Snake"; artefactDescription = "Increases damages"; break;
    default: break;
  }*/

  if (items[itemType].type == itemType)
  {
    artefactName = items[itemType].name;
    artefactDescription = items[itemType].description;
  }
  else
  {
    artefactName = "Unknown";
    artefactDescription = "Report to developper";
  }
}

ArtefactDescriptionEntity::~ArtefactDescriptionEntity()
{
}

void ArtefactDescriptionEntity::animate(float delay)
{

  if (age < ARTEFACT_ZOOM_TIME)
  {
    float perc = 1.0f - age / ARTEFACT_ZOOM_TIME;
    sprite.setScale(3.5f + perc * 50.0f, 3.5f + perc * 50.0f);
  }
  else
  {
    sprite.setScale(3.5f, 3.5f);
  }
  SpriteEntity::animate(delay);
}

void ArtefactDescriptionEntity::render(sf::RenderWindow* app)
{
    int nx = frame;
    int ny = 0;

    if (imagesProLine > 0)
    {
        nx = frame % imagesProLine;
        ny = frame / imagesProLine;
    }

    sprite.setTextureRect(sf::IntRect(nx * width, ny * height, /*(nx + 1) **/ width, /*(ny + 1) */ height));

    sprite.setPosition(x, y);
    sprite.setRotation(angle);

    if (isFading)
    {
        sprite.setColor(sf::Color(255, 255, 255, (sf::Uint8)(getFade() * 255)));
    }

    if (isShrinking)
    {
        sprite.setScale(getFade(), getFade());
    }


    app->draw(rectangleBorder);
    app->draw(rectangle);

    app->draw(sprite);

    StaticTextEntity::Write(app, artefactName, 22, 315.0f, ARTEFACT_POS_Y + 15.0f, ALIGN_LEFT, sf::Color(255, 255, 255));
    StaticTextEntity::Write(app, artefactDescription, 20, 315.0f, ARTEFACT_POS_Y + 55.0f, ALIGN_LEFT, sf::Color(255, 255, 255));
}

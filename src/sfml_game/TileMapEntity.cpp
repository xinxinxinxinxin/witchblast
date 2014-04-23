/**  This file is part of sfmlGame.
  *
  *  FreeTumble is free software: you can redistribute it and/or modify
  *  it under the terms of the GNU General Public License as published by
  *  the Free Software Foundation, either version 3 of the License, or
  *  (at your option) any later version.
  *
  *  FreeTumble is distributed in the hope that it will be useful,
  *  but WITHOUT ANY WARRANTY; without even the implied warranty of
  *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  *  GNU General Public License for more details.
  *
  *  You should have received a copy of the GNU General Public License
  *  along with FreeTumble.  If not, see <http://www.gnu.org/licenses/>.
  */

#include "TileMapEntity.h"

TileMapEntity::TileMapEntity(sf::Texture* image, GameMap* gameMap, int tileWidth, int tileHeight, int tilesProLine)
    : GameEntity(0.0f, 0.0f)
{
    this->image = image;
    this->tileWidth = tileWidth;
    this->tileHeight = tileHeight;
    this->tilesProLine = tilesProLine;
    this->gameMap = gameMap;
    this->z = -1.0f;

    type = 0;
    renderStates.texture = image;
    hasChanged = true;
}

TileMapEntity::~TileMapEntity()
{
}

void TileMapEntity::setMap(GameMap* gameMap)
{
  this->gameMap = gameMap;
  hasChanged = true;
}

int TileMapEntity::getTilesProLine()
{
    return tilesProLine;
}

bool TileMapEntity::getChanged()
{
  bool result = hasChanged;
  hasChanged = false;
  return result;
}

void TileMapEntity::computeVertices()
{
  vertices.setPrimitiveType(sf::Quads);
  vertices.resize(gameMap->getWidth() * gameMap->getHeight() * 4);

  for (int i = 0; i < gameMap->getWidth(); i++)
    for (int j = 0; j < gameMap->getHeight(); j++)
    {
      int nx = gameMap->getTile(i, j) % tilesProLine;
      int ny = gameMap->getTile(i, j) / tilesProLine;

      sf::Vertex* quad = &vertices[(i + j * gameMap->getWidth()) * 4];

      quad[0].position = sf::Vector2f(x + i * tileWidth, y + j * tileHeight);
      quad[1].position = sf::Vector2f(x + (i + 1) * tileWidth, y + j * tileHeight);
      quad[2].position = sf::Vector2f(x + (i + 1) * tileWidth, y + (j + 1) * tileHeight);
      quad[3].position = sf::Vector2f(x + i * tileWidth, y + (j + 1) * tileHeight);

      quad[0].texCoords = sf::Vector2f(nx * tileWidth, ny * tileHeight);
      quad[1].texCoords = sf::Vector2f((nx + 1) * tileWidth, ny * tileHeight);
      quad[2].texCoords = sf::Vector2f((nx + 1) * tileWidth, (ny + 1) * tileHeight);
      quad[3].texCoords = sf::Vector2f(nx * tileWidth, (ny + 1) * tileHeight);
    }
}

void TileMapEntity::render(sf::RenderWindow* app)
{
  app->draw(vertices, renderStates);
}

void TileMapEntity::animate(float delay)
{
    age += delay;
    bool needCompute = getChanged() || gameMap->getChanged();
    if (needCompute) computeVertices();
}

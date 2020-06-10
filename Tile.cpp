/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "Tile.h"

Tile::Tile(int x, int y)
{
	this->x = x;
	this->y = y;
	//bomb_icon = new FXGIFIcon(app, bomb, IMAGE_KEEP);
	//empty_icon = new FXGIFIcon(app, empty, IMAGE_KEEP);
	//this->setIcon(bomb_icon);

}

Tile::~Tile()
{
	//delete bomb_icon;
	//delete empty_icon;
}

void
Tile::disable_tile()
{
}

void
Tile::reveal()
{
	this->set_flag(REVEALED);
}

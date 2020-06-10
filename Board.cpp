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

#include "Board.h"

Board:: Board(int width, int height)
{
	this->width = width;
	this->height = height;
	this->tilecount = width*height;

	/* create tiles */
	for (int x = 0; x < height; x++)
	{
		for (int y = 0; y < width; y++)
		{
			std::shared_ptr<Tile> t(new Tile(x, y));
			tiles.push_back(t);
		}
	}
}

Board::~Board()
{
}

Tile *Board::get_tile_at(int x, int y)
{
	return tiles.at(this->width*x+y).get();
}
bool
Board::reveal_tile_at(int x, int y)
{
	Tile *tile = get_tile_at(x, y);
	printf("revealing x: %d y: %d\n", tile->get_x(), tile->get_y());
	return true;
}

void
Board::new_game(int x, int y)
{
}



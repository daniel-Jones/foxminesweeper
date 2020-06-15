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

//Board:: Board(int width, int height, int minecount)
Board:: Board()
{
	/*
	this->width = width;
	this->height = height;
	this->tilecount = width*height;
	this->minecount = minecount;
	this->game_running = true;
	this->game_won = false;

	// create tiles
	for (int x = 0; x < height; x++)
	{
		for (int y = 0; y < width; y++)
		{
			std::unique_ptr<Tile> t(new Tile(x, y));
			tiles.push_back(std::move(t));
		}
	}
	generate_mines();
	retrieve_neighbors();
	*/
}

Board::~Board()
{
	tiles.clear();
}

Tile *Board::get_tile_at(int x, int y)
{
	return tiles.at(this->height*x+y).get();
}

bool
Board::reveal_tile_at(int x, int y)
{
	Tile *tile = get_tile_at(x, y);
	if (tile->is_mine())
	{
		/* lose */
		reveal_all_mines();
		game_running = false;
		game_won = false;
		return false;
	}
	tile->reveal();
	reveal_neighbor_tiles(tile->get_x(), tile->get_y());
	if (check_win())
	{
		/* win */
		reveal_all_mines();
		game_won = true;
		game_running = false;
	}

	return true;
}

void
Board::new_game(int width, int height, int minecount)
{
	this->width = width;
	this->height = height;
	this->tilecount = width*height;
	this->minecount = minecount;
	this->game_running = true;
	this->game_won = false;
	tiles.clear();
	/* =reate tiles */
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			std::unique_ptr<Tile> t(new Tile(x, y));
			tiles.push_back(std::move(t));
		}
	}
	generate_mines();
	retrieve_neighbors();

}

void
Board::reveal_all_mines()
{
	Tile *tile;
	for(auto& t: tiles)
	{
		tile = t.get();
		/* explicitly unflag tile */
		tile->clear_flag(Tile::FLAGGED);
		if (tile->is_mine())
		{
			tile->set_flag(Tile::REVEALED);
		}
	}
}

void
Board::retrieve_neighbors()
{
	Tile *tile;
	int x, y;
	for (auto& t: tiles)
	{
		tile = t.get();
		x = t->get_x();
		y = t->get_y();
		int badup = 0, baddown = 0, badleft = 0, badright = 0;
		if (x-1<0) badleft = 1;
		if (x+1>width-1) badright = 1;

		if (y-1<0) badup = 1;
		if (y+1>height-1) baddown = 1;

		if (!badleft && !badup) tile->neighbors[0] = get_tile_at(x-1, y-1);
		if (!badup) tile->neighbors[1] = get_tile_at(x, y-1);
		if (!badright && !badup) tile->neighbors[2] = get_tile_at(x+1, y-1);

		if (!badleft) tile->neighbors[3] = get_tile_at(x-1, y);
		if (!badright) tile->neighbors[4] = get_tile_at(x+1, y);

		if (!badleft && !baddown) tile->neighbors[5] = get_tile_at(x-1, y+1);
		if (!baddown) tile->neighbors[6] = get_tile_at(x, y+1);
		if (!badright && !baddown) tile->neighbors[7] = get_tile_at(x+1, y+1);
		count_neighbor_mines(tile);
	}
}

void
Board::count_neighbor_mines(Tile *tile)
{
	Tile *neighbor;
	int mines = 0;
	for (int i = 0; i < 8; i++)
	{
		neighbor = tile->get_neighbor(i);
		if (neighbor)
		{
			if (neighbor->is_mine())
			{
				mines++;
			}
		}
	}
	tile->set_neighbor_mine_count(mines);
	//printf("init tile: x: %d, y: %d, neighbor mines: %d\n", tile->get_x(), tile->get_y(), tile->get_neighbor_mine_count());
}

void
Board::generate_mines()
{
	srand(time(NULL));
	int mx, my;
	Tile *tile;
	for (int i = 0; i < minecount; i++)
	{
replace_mine:
		mx = rand() % width;
		my = rand() % height;
		tile = get_tile_at(mx, my);
		if (tile->is_mine()) /* don't overwrite mines */
			goto replace_mine;
		tile->set_flag(Tile::MINE);
	}
}

bool
Board::reveal_neighbor_tiles(int x, int y)
{
	/*
	 * reveal all neighbor tiles that are empty, recursively
	 */

	Tile *tile, *neighbor;
	tile = get_tile_at(x, y);

	/* always reveal the first tile even if it has a neighbor mines */
	tile->set_flag(Tile::REVEALED);
	if (tile->is_mine())
		return false;
	if (tile->get_neighbor_mine_count() == 0)
	{
		/* if our tile is empty we want to reveal its immediate neighbors */
		for (int nc = 0; nc < 8; nc++)
		{
			neighbor = tile->get_neighbor(nc);
			if (neighbor != nullptr && !neighbor->is_mine() && !neighbor->is_revealed())
			{
				reveal_neighbor_tiles(neighbor->get_x(), neighbor->get_y());
			}
		}
	}
	return true;
}

bool
Board::check_win()
{
	int safetiles = (height * width) - minecount;
	int correcttiles = 0;

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			Tile *tile = get_tile_at(x, y);
			if (!(tile->is_mine()) && (tile->is_revealed()))
				correcttiles++;
		}
	}

	return (correcttiles == safetiles);
}

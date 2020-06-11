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

#include "MainWindow.h"
#include "fxdefs.h"
#include <cstdlib> // rand
#include <memory>
#include <stdio.h>

FXDEFMAP(MainWindow) MainWindow_Map[]=
{
	//________Message_Type____________ID____________Message_Handler_______
	FXMAPFUNC(SEL_COMMAND, MainWindow::UI_Tile, MainWindow::on_Tile_Click),
	FXMAPFUNC(SEL_COMMAND, MainWindow::UI_New, MainWindow::on_New_Click),
	FXMAPFUNC(SEL_RIGHTBUTTONPRESS, MainWindow::UI_Tile, MainWindow::on_Tile_Right_Click),
};
FXIMPLEMENT(MainWindow, FXMainWindow, MainWindow_Map, ARRAYNUMBER(MainWindow_Map))

MainWindow::MainWindow(FXApp *a)
	: FXMainWindow(a, "foxminesweeper", nullptr, nullptr, DECOR_ALL, 0,0,200,150)
{
	board = nullptr;
	matrix = nullptr;
	app = a;
	create_ui();
	int width = 15;
	int height = 15;
	int minecount = 33;
	game_over = false;
	new_game(width, height, minecount);
}

MainWindow::~MainWindow()
{
	delete board;
}

void
MainWindow::create()
{
	FXMainWindow::create();
	bomb_icon->create();
	flag_icon->create();
	empty_icon->create();
	tile_1_icon->create();
	tile_2_icon->create();
	tile_3_icon->create();
	tile_4_icon->create();
	tile_5_icon->create();
	tile_6_icon->create();
	tile_7_icon->create();
	tile_8_icon->create();
	show(PLACEMENT_SCREEN);
}

void
MainWindow::create_ui()
{
	contents=new FXHorizontalFrame(this, LAYOUT_SIDE_TOP|LAYOUT_FILL_X|LAYOUT_FILL_Y);

	// LEFT pane to contain the canvas
	canvasFrame=new FXVerticalFrame(contents, FRAME_SUNKEN|LAYOUT_FILL_X|LAYOUT_FILL_Y|LAYOUT_TOP|LAYOUT_LEFT, 0, 0, 0, 0, 10, 10, 10, 10);

	// Label above the canvas
	new FXLabel(canvasFrame,"foxminesweeper", NULL, JUSTIFY_CENTER_X|LAYOUT_FILL_X);
	// Horizontal divider line
	new FXHorizontalSeparator(canvasFrame, SEPARATOR_GROOVE|LAYOUT_FILL_X);

	scroll_area = new FXScrollWindow(canvasFrame, FX::SCROLLERS_NORMAL|LAYOUT_FILL_X|LAYOUT_FILL_Y|FRAME_SUNKEN);

	// RIGHT pane for the buttons
	buttonFrame=new FXVerticalFrame(contents, FRAME_SUNKEN|LAYOUT_FILL_Y|LAYOUT_TOP|LAYOUT_LEFT, 0, 0, 0, 0, 10, 10, 10, 10);

	// Label above the buttons
	new FXLabel(buttonFrame, "New Game", NULL, JUSTIFY_CENTER_X|LAYOUT_FILL_X);

	// Horizontal divider line
	new FXHorizontalSeparator(buttonFrame, SEPARATOR_RIDGE|LAYOUT_FILL_X);

	// Exit button
	new FXButton(buttonFrame, "&Exit", nullptr, app, FXApp::ID_QUIT, BUTTON_NORMAL|LAYOUT_FILL_X);
	new FXButton(buttonFrame, "&New Game", nullptr, this, MainWindow::UI_New, BUTTON_NORMAL|LAYOUT_FILL_X);
	/* create icons */
	bomb_icon = new FXGIFIcon(app, bomb, IMAGE_KEEP);
	flag_icon = new FXGIFIcon(app, flag, IMAGE_KEEP);
	empty_icon = new FXGIFIcon(app, empty, IMAGE_KEEP);
	tile_1_icon = new FXGIFIcon(app, tile_1, IMAGE_KEEP);
	tile_2_icon = new FXGIFIcon(app, tile_2, IMAGE_KEEP);
	tile_3_icon = new FXGIFIcon(app, tile_3, IMAGE_KEEP);
	tile_4_icon = new FXGIFIcon(app, tile_4, IMAGE_KEEP);
	tile_5_icon = new FXGIFIcon(app, tile_5, IMAGE_KEEP);
	tile_6_icon = new FXGIFIcon(app, tile_6, IMAGE_KEEP);
	tile_7_icon = new FXGIFIcon(app, tile_7, IMAGE_KEEP);
	tile_8_icon = new FXGIFIcon(app, tile_8, IMAGE_KEEP);
}

void
MainWindow::new_game(int width, int height, int minecount)
{
	if (board)
		delete board;
	puts("starting new game..");
	int tilecount = width*height;
	tile_buttons.clear();
	board = new Board(width, height, minecount);
	matrix = new FXMatrix(scroll_area, width, MATRIX_BY_COLUMNS|LAYOUT_CENTER_Y|LAYOUT_CENTER_X);
	for (int i = 0; i < tilecount; i++)
	{
		std::shared_ptr<FXButton> b(new FXButton(matrix, "", nullptr, this, UI_Tile));
		tile_buttons.push_back(b);
		b->setIcon(empty_icon);
	}
	printf("rows: %d columns: %d\n", matrix->getNumRows(), matrix->getNumColumns());
	draw_buttons();
}

void
MainWindow::draw_buttons()
{
	int x, y;
	FXButton *button;
	Tile *tile;
	for(auto b = tile_buttons.begin(); b != tile_buttons.end(); ++b)
	{
		button = (*b).get();
		x = matrix->colOfChild(button);
		y = matrix->rowOfChild(button);
		tile = board->get_tile_at(x, y);
		if (tile->is_flagged())
		{
			button->setIcon(flag_icon);
			button->setFrameStyle(0);
			continue;
		}
		 if (!tile->is_revealed())
		 {
			 button->setIcon(empty_icon);
			 button->setFrameStyle(BUTTON_NORMAL);
			continue;
		 }
		if (tile->is_mine())
		{
			button->setIcon(bomb_icon);
			button->setFrameStyle(0);
		}
		else
		{

			switch (tile->get_neighbor_mine_count())
			{
				case 1:
					button->setIcon(tile_1_icon);
					break;
				case 2:
					button->setIcon(tile_2_icon);
					break;
				case 3:
					button->setIcon(tile_3_icon);
					break;
				case 4:
					button->setIcon(tile_4_icon);
					break;
				case 5:
					button->setIcon(tile_5_icon);
					break;
				case 6:
					button->setIcon(tile_6_icon);
					break;
				case 7:
					button->setIcon(tile_7_icon);
					break;
				case 8:
					button->setIcon(tile_8_icon);
					break;
				default:
					button->setIcon(empty_icon);
					break;
			}
			button->setFrameStyle(0);
		}
	}
}

long
MainWindow::on_Tile_Click(FXObject *sender, FXSelector sel, void *data)
{
	if (game_over == true)
		return 1;
	int x = 0, y = 0;
	Tile *tile;
	FXButton *button = dynamic_cast<FXButton*>(sender);
	if (!button)
		return 0;
//	button->killFocus(); // let user control with keyboard
	x = matrix->colOfChild(button);
	y = matrix->rowOfChild(button);
	tile = board->get_tile_at(x, y);
	if (tile->is_revealed())
		return 1;
	if (tile->is_flagged())
		return 1;
	printf("left clicked on: x=%d, y=%d\n", x, y);
	board->reveal_tile_at(x, y);
	if (!board->is_game_running() && !board->is_game_won())
	{
		/* lost */
		puts("you lose the game");
		FXMessageBox *msgbox = new FXMessageBox(app, "Game Over", "You lost", nullptr, FX::MBOX_OK);
		msgbox->create();
		msgbox->show();
		game_over = true;
	}
	else if (!board->is_game_running() && board->is_game_won())
	{
		/* won */
		puts("you won the game");
		FXMessageBox *msgbox = new FXMessageBox(app, "Game Over", "You win", nullptr, FX::MBOX_OK);
		msgbox->create();
		msgbox->show();
		game_over = true;
	}
	button->setFrameStyle(0);
	draw_buttons();
	return 1;
}

long
MainWindow::on_Tile_Right_Click(FXObject *sender, FXSelector sel, void *data)
{
	if (game_over == true)
		return 1;
	int x = 0, y = 0;
	Tile *tile;
	FXButton *button = dynamic_cast<FXButton*>(sender);
	if (!button)
		return 0;
	x = matrix->colOfChild(button);
	y = matrix->rowOfChild(button);
	tile = board->get_tile_at(x, y);
	printf("right click on: %d, %d\n", tile->get_x(), tile->get_y());
	tile->toggle_flag(Tile::FLAGGED);
	printf("%d\n", tile->is_flagged());
	draw_buttons();
	return 1;
}

long
MainWindow::on_New_Click(FXObject *sender, FXSelector sel, void *data)
{
	if (board)
	{
		new_game(5, 5, 20);
	}
	return 1;
}

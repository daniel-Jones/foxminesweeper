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
#include "FXMessageBox.h"
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
	FXMAPFUNC(SEL_TIMEOUT, MainWindow::UI_Timer_Tick, MainWindow::on_Timer_Tick),
	FXMAPFUNC(SEL_KEYPRESS, 0, MainWindow::on_Key_Press),
	FXMAPFUNC(SEL_KEYRELEASE, 0, MainWindow::on_Key_Release),
};
FXIMPLEMENT(MainWindow, FXMainWindow, MainWindow_Map, ARRAYNUMBER(MainWindow_Map))

MainWindow::MainWindow(FXApp *a)
	: FXMainWindow(a, "foxminesweeper", nullptr, nullptr, DECOR_ALL, 0,0, 500, 500)
{
	board = new Board();
	matrix = nullptr;
	app = a;
	create_ui();
	int w = 9;
	int h = 9;
	int minecount = 10;
	game_count = 0;
	game_over = false;
	new_game(w, h, minecount);
}

MainWindow::~MainWindow()
{
	delete board;
}

long
MainWindow::on_Timer_Tick(FXObject *sender, FXSelector sel, void *data)
{
	seconds++;
	time_label->setText(FXStringVal(seconds));
	getApp()->addTimeout(this, UI_Timer_Tick, 1000, nullptr);
	return 1;
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
	time_label = new FXLabel(canvasFrame, "0", nullptr, LAYOUT_CENTER_X);
	// Horizontal divider line
	new FXHorizontalSeparator(canvasFrame, SEPARATOR_GROOVE|LAYOUT_FILL_X);

	scroll_area = new FXScrollWindow(canvasFrame, FX::SCROLLERS_NORMAL|LAYOUT_FILL_X|LAYOUT_FILL_Y|FRAME_SUNKEN);
	scroll_area->setBackColor(canvasFrame->getBackColor());

	// RIGHT pane for the buttons
	buttonFrame=new FXVerticalFrame(contents, FRAME_SUNKEN|LAYOUT_FILL_Y|LAYOUT_TOP|LAYOUT_LEFT, 0, 0, 0, 0, 10, 10, 10, 10);

	// Label above the buttons
	new FXLabel(buttonFrame, "New Game", NULL, JUSTIFY_CENTER_X|LAYOUT_FILL_X);

	// Horizontal divider line
	new FXHorizontalSeparator(buttonFrame, SEPARATOR_RIDGE|LAYOUT_FILL_X);

	// new / exit
	width_input_frame = new FXHorizontalFrame(buttonFrame, LAYOUT_SIDE_TOP|LAYOUT_FILL_X);
	height_input_frame = new FXHorizontalFrame(buttonFrame, LAYOUT_SIDE_TOP|LAYOUT_FILL_X);
	mine_input_frame = new FXHorizontalFrame(buttonFrame, LAYOUT_SIDE_TOP|LAYOUT_FILL_X);

	new FXLabel(width_input_frame, "Width: ", NULL, LAYOUT_BOTTOM|LAYOUT_FILL_X);
	width_input = new FXTextField(width_input_frame, 3, NULL, 0, TEXTFIELD_NORMAL|TEXTFIELD_INTEGER);
	width_input->setText("9");
	new FXLabel(height_input_frame, "Height: ", NULL, LAYOUT_BOTTOM|LAYOUT_FILL_X);
	height_input = new FXTextField(height_input_frame, 3, NULL, 0, TEXTFIELD_NORMAL|TEXTFIELD_INTEGER);
	height_input->setText("9");
	new FXLabel(mine_input_frame, "Mines: ", NULL, LAYOUT_BOTTOM|LAYOUT_FILL_X);
	mine_input = new FXTextField(mine_input_frame, 3, NULL, 0, TEXTFIELD_NORMAL|TEXTFIELD_INTEGER);
	mine_input->setText("10");

	new FXButton(buttonFrame, "&New Game", nullptr, this, MainWindow::UI_New, BUTTON_NORMAL|LAYOUT_FILL_X);
	new FXButton(buttonFrame, "&Exit", nullptr, app, FXApp::ID_QUIT, BUTTON_NORMAL|LAYOUT_FILL_X|LAYOUT_BOTTOM);
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
MainWindow::new_game(int w, int h, int minecount)
{
	tile_buttons.clear();
	game_count++;
	seconds = 0;
	ticking = false;
	//delete board;
	delete matrix;
	puts("starting new game..");
	int tilecount = w*h;
	printf("tile count will be %d\n", tilecount);
	//board = new Board(width, height, minecount);
	board->new_game(w, h, minecount);
	matrix = new FXMatrix(scroll_area, w, MATRIX_BY_COLUMNS|LAYOUT_CENTER_Y|LAYOUT_CENTER_X);
	if (game_count > 1)
		matrix->create();
	for (int i = 0; i < tilecount; i++)
	{
		std::unique_ptr<FXButton> b(new FXButton(matrix, "", nullptr, this, UI_Tile));
		b->setIcon(empty_icon);
		if (game_count > 1)
			b->create();
		tile_buttons.push_back(std::move(b));
	}
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
		if (x < 0 || y < 0)
			return;
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
			button->setBackColor(FXRGB(255, 0, 0)); // make mines red
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
	puts("click");
	if (!ticking)
	{
		app->addTimeout(this, UI_Timer_Tick, 1000);
		ticking = true;
	}
	if (game_over == true)
	{
		puts("game is over");
		return 1;
	}
	int x = 0, y = 0;
	Tile *tile;
	FXButton *button = dynamic_cast<FXButton*>(sender);
	if (!button)
	{
		printf("button is null");
		return 1;
	}
	puts("running click methods");
	button->killFocus(); // let user control with keyboard?
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
		draw_buttons();
		app->removeTimeout(this, UI_Timer_Tick);
		puts("you lose the game");
		app->beep();
		FXMessageBox::information(app, FX::MBOX_OK, "Game Over", "You lost in %ld seconds.", seconds);
		game_over = true;
		ticking = false;
	}
	else if (!board->is_game_running() && board->is_game_won())
	{
		/* won */
		draw_buttons();
		app->removeTimeout(this, UI_Timer_Tick);
		puts("you won the game");
		app->beep();
		FXMessageBox::information(app, FX::MBOX_OK, "Game Over", "You won in %ld seconds.", seconds);
		game_over = true;
		ticking = false;
	}
	button->setFrameStyle(0);
	draw_buttons();
	return 1;
}

long
MainWindow::on_Tile_Right_Click(FXObject *sender, FXSelector sel, void *data)
{
	if (!ticking)
	{
		app->addTimeout(this, UI_Timer_Tick, 1000);
		ticking = true;
	}
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
	if (tile->is_revealed())
		return 1;
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
		int w, h, m;
		w = FXIntVal(width_input->getText());
		h = FXIntVal(height_input->getText());
		m = FXIntVal(mine_input->getText());

		if (w == 0 || h == 0 || m == 0)
		{
			/* all fields need values */
			app->beep();
			FXMessageBox::information(app, FX::MBOX_OK, "Invalid game options", "All fields need positive (non-zero) integer values");
			return 1;
		}

		if (m >= (w*h))
		{
			/* cannot have >= mines that tiles */
			app->beep();
			FXMessageBox::information(app, FX::MBOX_OK, "Invalid game options", "You cannot have the same or more mines than tiles (mines >= (width*height))");
			return 1;
		}

		printf("new game width = %d height = %d mines = %d\n", w, h, m);
		game_over = false;
		time_label->setText("0");
		app->removeTimeout(this, UI_Timer_Tick);
		new_game(w, h, m);
	}
	return 1;
}

long
MainWindow::on_Key_Press(FXObject *sender, FXSelector sel, void *data)
{
	FXEvent* event=(FXEvent*)data;
	switch(event->code)
	{
		/* show mine positons while left control held */
		case KEY_Control_L:
			FXButton *button;
			Tile *tile;
			int x, y;
			for(auto b = tile_buttons.begin(); b != tile_buttons.end(); ++b)
			{
				button = (*b).get();
				x = matrix->colOfChild(button);
				y = matrix->rowOfChild(button);
				tile = board->get_tile_at(x, y);
				if (tile->is_mine())
				{
					button->setBackColor(FXRGB(0, 255, 0)); // make mines green
				}
			}
			break;
		default:
			this->onKeyPress(sender, sel, data);
			break;
	}
	return 1;
}

long
MainWindow::on_Key_Release(FXObject *sender, FXSelector sel, void *data)
{
	FXEvent* event=(FXEvent*)data;
	switch(event->code)
	{
		case KEY_Control_L:
			FXButton *button;
			Tile *tile;
			int x, y;
			for(auto b = tile_buttons.begin(); b != tile_buttons.end(); ++b)
			{
				button = (*b).get();
				x = matrix->colOfChild(button);
				y = matrix->rowOfChild(button);
				tile = board->get_tile_at(x, y);
				if (tile->is_mine())
				{
					button->setBackColor(canvasFrame->getBackColor()); // make mines normal
				}
			}
			break;

		default:
			this->onKeyPress(sender, sel, data);
			break;
	}

	return 1;
}

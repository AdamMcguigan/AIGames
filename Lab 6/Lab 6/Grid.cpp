#include "Grid.h"

void Grid::setUpCellIDNumText(sf::Font& m_font)
{
	for (int i = 0; i < MAX_CELLS; i++)
	{
		gridNum[i].setFont(m_font);
		gridNum[i].setScale(0.4, 0.4);
		gridNum[i].setFillColor(sf::Color::Black);
	}
}

Cell* Grid::atIndex(int t_id)
{
	int x = t_id % MAX_ROWS;
	int y = t_id / MAX_COLS;

	return 	&m_theTableVector.at(x).at(y);
}

Grid::Grid()
{
	setupGrid();
}

Grid::~Grid()
{
}

void Grid::createHeatMap(Cell* t_startCell, Cell* t_endpoint)
{
	int  num;
	Cell* v = t_endpoint;
	v->setCostDistance(0);
	/*num = 0;
	while (v->getNeighbours().size() != 0 &&v->getNeighbours().front()->getMarked()==false)
	{
		v = v->getNeighbours().front();
		v->setCostDistance(num + 1);
	}*/


	int r = 140;
	int g = 100;
	int b = 20;

	for (int i = 0; i < MAX_CELLS; i++)
	{
		v = atIndex(i);
		if (v->getTraversable() == true)
		{
			r++;
			g++;
			b++;
			sf::Color color(r, g, b);
			v->setCostDistance((abs(t_endpoint->xPos - v->xPos) + abs(t_endpoint->yPos - v->yPos)));
			v->setColor(color);
		}
		else {
			v->setCostDistance(999);
		}

		num = v->getCostDistance();
		gridNum[i].setPosition(v->getRect().getPosition().x, v->getRect().getPosition().y);
		gridNum[i].setString(std::to_string(num));
	}

	m_theTableVector;
	heatMapCreated = true;
}

void Grid::setIntraversable()
{
	int random;
	Cell* tempNode;
	std::srand(std::time(nullptr));

	for (int i = 0; i < 300; i++)
	{
		random = rand() % (2499 + 1);
		tempNode = atIndex(random);
		tempNode->setTraversable(false);
		if (tempNode->getTraversable() == false)
		{
			random = rand() % (2499 + 1);
			tempNode = atIndex(random);
			tempNode->setTraversable(false);
		}

	}


}

void Grid::setNeighbours(Cell* t_cell)
{
	int row = t_cell->xPos;
	int col = t_cell->yPos;

	for (int direction = 0; direction < 9; direction++) {
		if (direction == 4) continue;

		int n_row = row + ((direction % 3) - 1); // Neighbor row
		int n_col = col + ((direction / 3) - 1); // Neighbor column

		// Check the bounds:
		if (n_row >= 0 && n_row < MAX_ROWS && n_col >= 0 && n_col < MAX_COLS) {

			int id = n_row + (n_col * MAX_ROWS);// this is for the total number of rows you want in your grid i.e 50x50 or a 10x10
			t_cell->setNeighbours(atIndex(id));

		}
	}


}

void Grid::selectStartEndPos(sf::RenderWindow& t_window)
{
	const  sf::RenderWindow& m_window = t_window;
	sf::Vector2f m_MousePos = sf::Vector2f{ sf::Mouse::getPosition(m_window) };

	for (int i = 0; i < MAX_ROWS; i++)
	{
		for (int j = 0; j < MAX_COLS; j++)
		{
			if (m_theTableVector.at(i).at(j).getRect().getGlobalBounds().contains(m_MousePos))
			{
				if (m_startPosChosen == false)
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						std::cout << m_theTableVector.at(i).at(j).getID() << std::endl;
						m_theTableVector.at(i).at(j).setStartColour();
						m_theTableVector.at(i).at(j).setStartPoint(true);
						startId = m_theTableVector.at(i).at(j).getID();
						m_startPosChosen = true;

					}
				}
				if (m_endPosChosen == false)
				{
					// for the start position  for the algorithim
					if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
					{
						std::cout << m_theTableVector.at(i).at(j).getID() << std::endl;
						m_theTableVector.at(i).at(j).setEndColour();
						m_theTableVector.at(i).at(j).setEndPoint(true);
						endId = m_theTableVector.at(i).at(j).getID();
						m_endPosChosen = true;
					}

				}

			}

		}
	}
	if (m_endPosChosen == true && m_startPosChosen == true && heatMapCreated == false)
	{
		Cell* endCell;
		Cell* StartCell;
		StartCell = atIndex(startId);
		endCell = atIndex(endId);
		createHeatMap(StartCell, endCell);
	}


}

void Grid::setupGrid()
{
	sf::Vector2f pos{ 0.0f,0.f };
	for (int i = 0; i < MAX_ROWS; i++)
	{
		std::vector<Cell> tempVec;
		m_theTableVector.push_back(tempVec);
	}

	for (int i = 0; i < MAX_CELLS; i++)
	{
		int x = i % MAX_ROWS;
		int y = i / MAX_COLS;
		Cell tempNode;
		tempNode.xPos = x;
		tempNode.yPos = y;
		tempNode.initRect();
		tempNode.setPos(pos);
		pos.x += tempNode.getRect().getSize().x;
		if (pos.x == ScreenSize::M_WIDTH)
		{
			pos.y += tempNode.getRect().getSize().y;
			pos.x = 0;
		}
		tempNode.setID(x + (y * MAX_ROWS));

		m_theTableVector.at(x).push_back(tempNode);
	}


	for (int i = 0; i < MAX_CELLS; i++)
	{
		setNeighbours(atIndex(i));
	}
	m_theTableVector;
	int i = 0;

	setIntraversable();


}

void Grid::render(sf::RenderWindow& t_window)
{


	for (int i = 0; i < MAX_ROWS; i++)
	{
		for (int j = 0; j < MAX_COLS; j++)
		{
			t_window.draw(m_theTableVector.at(j).at(i).getRect());
		}
	}
	for (int i = 0; i < MAX_CELLS; i++)
	{
		t_window.draw(gridNum[i]);
	}
}

void Grid::update(sf::Time& t_deltatime)
{

}

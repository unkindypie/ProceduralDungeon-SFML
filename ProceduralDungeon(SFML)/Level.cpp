#include "Level.h"
#include "Player.h"
#include "Guntrap.h"
#include "Blade.h"
Level::Level()
{
	Sublevel::X_SIZE = levelWidth = 1000000;
	Sublevel::Y_SIZE = levelHeight = 720 / 32;
	LevelGenerationState gs = normal;
	Sublevel sub = Sublevel(0, 0, right_, exit_, gs, rm);
	level.push_back(sub);
	int lastWidth = level[level.size() - 1].getWidth();
	for(int i = 0; i < 20; i++){
		sub = Sublevel(lastWidth, 0, 0, level[level.size() - 1].getExitPosY(), 0, gs, rm);
		sub.addExit(right_, rm);
		level.push_back(sub);
		lastWidth += sub.getWidth();
	}
	for (int i = 0; i < level.size() - 1; i++)
	{
		level[i].next = &level[i + 1];
	}
	for (int i = level.size() - 1; i > 0; i--)
	{
		level[i].prev = &level[i - 1];
	}
	

	player = new Player((level[0].getWidth() / 2) * COMMON_SPRITE_SIZE, (level[0].getHeight() / 2) * COMMON_SPRITE_SIZE, &level[0], rm);

	level[0].addEntity(player);
}
Level::Level(size_t levelWidth, size_t levelHeight) //� ���� ������������ ��������� �������� ����� ��������� ����������� ��������� �����. �� ��������� ����������, �� ������ ��������� �� ������� � �� ����, ������ ��� ������ ��� �� ��� �� ������������
{
	//current_shader = rm.loadShader("lightning");

	Sublevel::X_SIZE = levelHeight;
	Sublevel::Y_SIZE = levelWidth;
	this->levelHeight = levelHeight;
	this->levelWidth = levelWidth;
	sublevelLineState state; //����� - ��������� ����� ���������� ��� ������������ �����, �� � ������� ������ �����.
	//rightEnterLeftExit - ��������� ����� ���������� � ������ ������� ������ � ������� ����� �����
	//leftEnterRightExit - ��������
	LevelGenerationState generationState = normal; //����������, ���������� �� ��������� � �������� ������������ ����� � ������������� ����������. ���� ����� ���������, �� ������� ����� ���������� ������.
	size_t lx;
	size_t ly;
	float enterX; //����������� ������� ������ �� ��������-����� � ��������� 
	float enterY;
	vector<int> sublevelHorizontalLineHeight; //������ ��� �������� ����� ����� ������� ��������� �� ���������. ��������� ��� ����, ����� ����� �� ����� ���������� �� y ������ ����������
	Sublevel sub;
	int lenght = 0; //����� ������ ����� �� ���������� �� �����������
	do //������ ���� ��������� ��� ��������� ��������� ������������� Sublevel � ��������� ������������ �����. ��� ������, ����� �� ���������� ������� ���������� � ��������� ����� ���������
		//��-�� ������������ �� ������. �� ����, � ����� �������� ��������� ���������� � ������� �������� ��������, � � ������ ������� ����������. � ����� ������ ����������� ��������� ����������
		// � generationState �������� restart � ������� �� �����. �� ��������� ���������� ����� normal, �� ������ ��� ��� do while ���� ���������� ���� ���.
	{
		state = start; //������ ��������� ������ ���� � �����
		generationState = normal; //������ ��������� ��������� � ����������
		lx = 0;
		ly = 0;
		enterX = -1; //���������� -1 �� ����� ����, �� ����� ��� ����� ����������� ����������� �����
		enterY = -1;
		level.clear();
		sublevelHorizontalLineHeight.clear();
		sub = Sublevel(lx, ly, right_, exit_, generationState, rm); //������ ������ ��������� �������, � ������� ����� ������ �����
		lenght = 0;

		do //������ ���� ��������� ��� ����������� ����� �� ����������. �� ���� ���� ������ ������, ����� ����� ����� � ���� ����� ������ � ����� ������ �����
			//���� ��������� ��-�� ����, ��� ���������� ������� ������ ���������� ����� ���������� �� ������ �.�. �� �������� ���������� ����������� rightEnterLeftExit � leftEnterRightExit
			//start ���������� ���� ��� � ������ � ���� � ���� �� ������
		{
			switch (state)
			{
			case start: //�� ����� ������ ��������� ����� ������ ����� �� ���������� � ������������ ������� � �������. � ������ ������ ������������ ����� ������ ������.
			{
				while (lx < levelWidth - 3)
				{
					level.push_back(sub);
					sublevelHorizontalLineHeight.push_back(sub.getHeight()); //�������� ������ �����
					lx += sub.getWidth();
					enterX = sub.getExitPosX(); 
					enterY = sub.getExitPosY();
					sub = Sublevel(lx, ly, 0, enterY, 0, generationState, rm);

					if(generationState == restart)
					{
						break;
					}
					
					sub.addExit(right_, rm);
					lenght++;
				}
				if (generationState == restart)
				{
					break;
				}
				dynamic_cast<Block*>(level[lenght - 1].getMap()[level[lenght - 1].getExitPosY()][level[lenght - 1].getExitPosX()])->setBlockType(brick, rm, right_);
			

				level[lenght - 1].addExit(down, rm); //������ ����� ����� ����� ��� ����
				level[lenght - 1].makeItAngle();
			
				state = rightEnterLeftExit;
				enterX = level[lenght - 1].getExitPosX();
				enterY = level[lenght - 1].getExitPosY();
			}
			break;
			case rightEnterLeftExit:
			{
				sub = Sublevel(level[lenght - 1].getX(), sublevelHorizontalLineHeight[lenght - 1], level[lenght - 1].getWidth(), enterX, 0, 0, generationState, y_sided, rm);
				sublevelHorizontalLineHeight[lenght - 1] += sub.getHeight(); //���������� ������ ����������� ���������� �� ���� ������ ������ ���������. ������ ��� ����� ����� y ��� ���������� ���������
				sub.addExit(left_, rm); //�������� ����� � ����� ������ ���������
				enterX = sub.getExitPosX(); //������� ���������� ������ �� ����� ���������
				enterY = sub.getExitPosY();
				//level.insert(level.begin() + lenght, sub);
				level.push_back(sub);
				for (int i = lenght - 2; i >= 0; i--)
				{
					sub.getExitGlobalCoords(enterX, enterY); //������� ���������� ������ �� �������� ��������� � �������� ����� ������(�� ����, �� ������������ ������ ���������)
					sub = Sublevel(level[i].getX(), sublevelHorizontalLineHeight[i], level[i].getWidth(), level[i].getWidth() - 1, enterY / COMMON_SPRITE_SIZE - sublevelHorizontalLineHeight[i], 0, generationState, x_sided, rm);
					//������ �������� ��� x ������� �������� ���������, 
					//������ ��� ������� ������� ������� �������� �� ������� �����, 
					//������ ��� ������ �������� ���������(� ��� ��� �� ����� ����������) � ������� �� ������
					//��������� ��� ������-1 �.�. ������� ����� � ���������� �� X(�� ���� ����� ������ ������)
					//����� ��� ������� ����� ���������� ����������� ������ �� �������� ��������� � ������� ������� ����� �������� ���������� - � ���������� ���������� ���������� ������������ ������ ����� ���������
					//������ 0 - ��� ������� � ��������� - ����
					//������������� ���������� ������/����� ����� ��-�� ����� � ������������ ���������, ������� ����������� ����� � ����������� �� ������� �������� i � j ������� ���������� �� ����
					if (generationState == restart)
					{
						break;
					}
					sublevelHorizontalLineHeight[i] += sub.getHeight(); //���������� ������ ����������� ���������� �� ���� ������ ������ ���������. ������ ��� ����� ����� y ��� ���������� ���������
					sub.addExit(left_, rm); //�������� ����� � ����� ����������
				
					level.push_back(sub);
				}
				if (generationState == restart)
				{
					break;
				}

				//������ ������ ����� �����, ������ ���� ����� ����� ����
				dynamic_cast<Block*>(level[level.size() - 1].getMap()[level[level.size() - 1].getExitPosY()][level[level.size() - 1].getExitPosX()])->setBlockType(brick, rm, left_);
				
				level[level.size() - 1].makeItAngle(); //����� ���� ���������� �������(� ��� �� ����� ��������� �������)

				level[level.size() - 1].addExit(down, rm); //������ ����� ����� ����� ��� ����

				enterX = level[level.size() - 1].getExitPosX(); //������� ���������� ������ �� ����� ���������
				enterY = level[level.size() - 1].getExitPosY();
				state = leftEnterRightExit;//������� ��������� ����� ���������� �� ������ �����
			}
				break;
			case leftEnterRightExit:
			{
				sub = Sublevel(level[0].getX(), sublevelHorizontalLineHeight[0], level[0].getWidth(), enterX, 0, 0, generationState, y_sided, rm);
				sublevelHorizontalLineHeight[0] += sub.getHeight(); //���������� ������ ����������� ���������� �� ���� ������ ������ ���������. ������ ��� ����� ����� y ��� ���������� ���������
				sub.addExit(right_, rm); //�������� ����� � ����� ������ ���������
				//level.insert(level.begin() + lenght, sub);
				level.push_back(sub);

				for (int i = 1; i < lenght; i++)
				{
					sub.getExitGlobalCoords(enterX, enterY); //������� ���������� ������ �� �������� ��������� � �������� ����� ������(�� ����, �� ������������ ������ ���������)
					sub = Sublevel(level[i].getX(), sublevelHorizontalLineHeight[i], level[i].getWidth(), 0, enterY / COMMON_SPRITE_SIZE - sublevelHorizontalLineHeight[i], 0, generationState, x_sided, rm);
				
					//������ �������� ��� x ������� �������� ���������, 
					//������ ��� ������� ������� ������� �������� �� ������� �����, 
					//������ ��� ������ �������� ���������(� ��� ��� �� ����� ����������) � ������� �� ������
					//��������� ��� ������-1 �.�. ������� ����� � ���������� �� X(�� ���� ����� ������ ������)
					//����� ��� ������� ����� ���������� ����������� ������ �� �������� ��������� � ������� ������� ����� �������� ���������� - � ���������� ���������� ���������� ������������ ������ ����� ���������
					//������ 0 - ��� ������� � ��������� - ����
					//������������� ���������� ������/����� ����� ��-�� ����� � ������������ ���������, ������� ����������� ����� � ����������� �� ������� �������� i � j ������� ���������� �� ����
					if (generationState == restart)
					{
						break;
					}
					sublevelHorizontalLineHeight[i] += sub.getHeight(); //���������� ������ ����������� ���������� �� ���� ������ ������ ���������. ������ ��� ����� ����� y ��� ���������� ���������
					sub.addExit(right_, rm); //�������� ����� � ����� ����������
					enterX = sub.getExitPosX(); //������� ���������� ������ �� ����� ���������
					enterY = sub.getExitPosY();
					level.push_back(sub);
				}
				if (generationState == restart)
				{
					break;
				}
				//����� ����� �� �������� � ������ ������
				dynamic_cast<Block*>(level[level.size() - 1].getMap()[level[level.size() - 1].getExitPosY()][level[level.size() - 1].getExitPosX()])->setBlockType(brick, rm, right_);

				level[level.size() - 1].addExit(down, rm); //������ ����� ����� ����� ��� ����

				level[level.size() - 1].makeItAngle();

				enterX = level[level.size() - 1].getExitPosX(); //������� ���������� ������ �� ����� ���������
				enterY = level[level.size() - 1].getExitPosY();
				state = rightEnterLeftExit;
			}
				break;
			default:
				break;
			}
		} while (sublevelHorizontalLineHeight[0] < levelHeight - 3 && generationState != restart);

		dynamic_cast<Block*>(level[level.size() - 1].getMap()[level[level.size() - 1].getExitPosY()][level[level.size() - 1].getExitPosX()])->setBlockType(brick, rm, down);

		level[level.size() - 1].makeItAngle();


	} while (generationState == restart);

	for(int i = 0; i < level.size()-1; i++)
	{
		level[i].next = &level[i + 1];
	}
	for (int i = level.size() - 1; i > 0 ; i--)
	{
		level[i].prev = &level[i - 1];
	}
	SublevelFillingType stype;
	for(int i = 1; i < level.size();i++)
	{
		if(!level[i].isAngle())
		{
			stype = SublevelFillingType(randomNumber(0, 3));
			if(stype > 0)
			{
				level[i].fill(guntrapped_vertical, rm);
			}
			else
			{
				level[i].fill(razer, rm);
			}
			
		}
	}
	player = new Player((level[0].getWidth() / 2) * COMMON_SPRITE_SIZE, (level[0].getHeight() / 2) * COMMON_SPRITE_SIZE, &level[0], rm);
	level[0].addEntity(player);
	//size_t pos = level.size()-2;
	//player = new Player((level[pos].getWidth() / 2) * COMMON_SPRITE_SIZE, (level[pos].getHeight() / 2) * COMMON_SPRITE_SIZE, &level[pos], rm);
	//level[pos].addContent(player);
	
	
}

ResourceManager & Level::getResourceManager()
{
	return rm;
}
int Level::getPlayerTries()
{
	return dynamic_cast<Player*>(player)->getTries();
}
vector<Sublevel> & Level::getLevelMap()
{
	return level;
}
void Level::draw(sf::RenderWindow & win)
{
	//�������� ���� � ���, ����� ���� ��������� ����� ������ �� ��� ������, ������� �������� ������ � ���� ������, � �� �������� ��� ������ ����, ������� �� ���� �����
	sf::FloatRect viewRect = { win.getView().getCenter().x - win.getSize().x / 2, win.getView().getCenter().y - win.getSize().y / 2, (float)win.getSize().x, (float)win.getSize().y };//������� ������������� ����
	for (int sub = 0; sub < level.size(); sub++) //������ �� ������� ���������� ������
	{
		//������� ���������� ����(���� ������) � ���� ������, � �� ��������
		int startY = viewRect.top / COMMON_SPRITE_SIZE;
		int endY = (viewRect.top + viewRect.height) / COMMON_SPRITE_SIZE;
		int startX = viewRect.left / COMMON_SPRITE_SIZE;
		int endX = (viewRect.left + viewRect.width) / COMMON_SPRITE_SIZE;
		if (startY < 0) startY = 0;
		if (startX < 0) startX = 0;
		//��� ������ ���� �������� �� ����� ��������� ���� �� ������� ������. �� � ������ �� ��������, ��� �� ����� ���
		
		//���� ���������� ��������� �� ������������ ����, �� ��������� ��������
		if (startY >= level[sub].getY() + level[sub].getHeight() || endY <= level[sub].getY()
			|| startX >= level[sub].getX() + level[sub].getWidth() || endX <= level[sub].getX()) continue;

		//������� ���������� ����������� ���������� � �����, ���� ����� ���� ������ ������ �� ��� ������, ������� ��������� � ���� ������
		int beginY = startY - level[sub].getY();
		int finalY = endY - level[sub].getY();

		if (beginY < 0) beginY = 0;
		if (finalY > level[sub].getHeight()) finalY = level[sub].getHeight();

		int beginX = startX - level[sub].getX();
		int finalX = endX - level[sub].getX();

		if (beginX < 0) beginX = 0;
		if (finalX > level[sub].getWidth()) finalX = level[sub].getWidth();

		//���� ��������� ������, ���� ������� � ��� ���� ���� ���� ������. ��� ��� ���� ����, ����� ���� �� ����������� ������ ��������, ��� ����� �������� ���������
		for(int i = beginY; i < finalY; i++)
		{
			for (int j = beginX; j < finalX; j++)
			{
				level[sub].getMap()[i][j]->draw(win);
			}
		}
		//��������� ���������
		for (int k = 0; k < level[sub].getEntities().size(); k++)
		{
				level[sub].getEntities()[k]->draw(win);
				/*if(level[sub].getEntities()[k]->getShader() == (*current_shader).first)
				{
					
				}*/
				DebugInformation::getInstance().renderedEntitiesCounter++;
		}

	}
}
void Level::draw(sf::RenderTexture & rendTexture, vector<sf::Glsl::Vec2> & lightEmiters, sf::FloatRect viewRect)
{
	//�������� ���� � ���, ����� ���� ��������� ����� ������ �� ��� ������, ������� �������� ������ � ���� ������, � �� �������� ��� ������ ����, ������� �� ���� �����
	//sf::FloatRect viewRect = { view.getCenter().x - rendTexture.getSize().x / 2, view.getCenter().y - rendTexture.getSize().y / 2, (float)rendTexture.getSize().x, (float)rendTexture.getSize().y };//������� ������������� ����
	
	for (int sub = 0; sub < level.size(); sub++) //������ �� ������� ���������� ������
	{
		//������� ���������� ����(���� ������) � ���� ������, � �� ��������
		int startY = viewRect.top / COMMON_SPRITE_SIZE;
		int endY = (viewRect.top + viewRect.height) / COMMON_SPRITE_SIZE;
		int startX = viewRect.left / COMMON_SPRITE_SIZE;
		int endX = (viewRect.left + viewRect.width) / COMMON_SPRITE_SIZE;
		if (startY < 0) startY = 0;
		if (startX < 0) startX = 0;
		//��� ������ ���� �������� �� ����� ��������� ���� �� ������� ������. �� � ������ �� ��������, ��� �� ����� ���

		//���� ���������� ��������� �� ������������ ����, �� ��������� ��������
		if (startY >= level[sub].getY() + level[sub].getHeight() || endY <= level[sub].getY()
			|| startX >= level[sub].getX() + level[sub].getWidth() || endX <= level[sub].getX()) continue;

		//������� ���������� ����������� ���������� � �����, ���� ����� ���� ������ ������ �� ��� ������, ������� ��������� � ���� ������
		int beginY = startY - level[sub].getY();
		int finalY = endY - level[sub].getY();

		if (beginY < 0) beginY = 0;
		if (finalY > level[sub].getHeight()) finalY = level[sub].getHeight();

		int beginX = startX - level[sub].getX();
		int finalX = endX - level[sub].getX();

		if (beginX < 0) beginX = 0;
		if (finalX > level[sub].getWidth()) finalX = level[sub].getWidth();

		//���� ��������� ������, ���� ������� � ��� ���� ���� ���� ������. ��� ��� ���� ����, ����� ���� �� ����������� ������ ��������, ��� ����� �������� ���������
		for (int i = beginY; i < finalY; i++)
		{
			for (int j = beginX; j < finalX; j++)
			{
				level[sub].getMap()[i][j]->draw(rendTexture);
			}
		}
		//��������� ���������
		for (int k = 0; k < level[sub].getEntities().size(); k++)
		{
			level[sub].getEntities()[k]->draw(rendTexture);
			if(level[sub].getEntities()[k]->getShader() == string("lightning")/*(*current_shader).first*/)//������� ���������� ����������, � ������� ���� �������� �������
			{
				//�������� ���������� � ������ ������ ���� � ����, ��� � ������ glsl �� y ���������� ��������� ��������
				lightEmiters.push_back(sf::Glsl::Vec2((level[sub].getEntities()[k]->getX() - viewRect.left)*GlobalValues::zoomScaleFactor, (viewRect.height + viewRect.top - level[sub].getEntities()[k]->getY())*GlobalValues::zoomScaleFactor));
			}
			DebugInformation::getInstance().renderedEntitiesCounter++;
		}

	}
}
void Level::update(sf::FloatRect viewRect)
{
	for (int sub = 0; sub < level.size(); sub++) //������ �� ������� ���������� ������
	{
		for (int k = 0; k < level[sub].getEntities().size(); k++)
		{
			if(level[sub].getEntities()[k]->getRect().intersects(viewRect)) //���� �������� � ���� ������, �� �������� ��
			{
				DebugInformation::getInstance().updatedEntitiesCounter++;
				level[sub].getEntities()[k]->update();
			}
			else if(!level[sub].getEntities()[k]->isIndependent()) //������ ����������������� ��������, ���������� �� ������� ���� ������
			{
				Content * ptr = level[sub].getEntities()[k];
				level[sub].getEntities().erase(level[sub].getEntityIterator(level[sub].getEntities()[k]));
				delete ptr;
			}
		}
	}
}
bool Level::isGameOver()
{
	return dynamic_cast<Player*>(player)->isGameOver();
}
bool Level::isLevelPassed()
{
	return dynamic_cast<Player*>(player)->isLevelPassed();
}
map<string, sf::Shader*>::iterator & Level::getCurrentShader()
{
	return current_shader;
}
Level::~Level()
{
}

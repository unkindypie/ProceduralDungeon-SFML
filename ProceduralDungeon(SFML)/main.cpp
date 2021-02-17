#include "Level.h"
#include "GameInterface.h"
#include "Background.h"

int main()
{
	srand(time(NULL));
	GlobalValues gl;
	sf::RenderWindow window(sf::VideoMode(GlobalValues::getWindowWidth(), GlobalValues::getWindowHeight()), L"TODO: Придумать игре название"); //класс окна, в этой строчке я указываю его разрешение и название

	sf::RenderTexture renderTexture;
	renderTexture.create(window.getSize().x, window.getSize().y);

	sf::Clock updateClock; //класс счетчик времени, позволяет засекать и сбрасывать насчитанное время.
	Level level(70/*WINDOW_WIDTH / COMMON_SPRITE_SIZE*/, 70/*WINDOW_HEIGHT / COMMON_SPRITE_SIZE*/); //создаю уровень
	GameCamera cam(level.player, renderTexture); //игровая камера будет следить за игркоом
	GameInterface interf(&level, cam); //интерфейс будет выводить жизни игрока относительно координат камеры
	updateClock.restart();

	float frames = GlobalValues::getFpsLimit();
	float frameOffset = 1000 / frames;
	float nextUpdate = updateClock.getElapsedTime().asMilliseconds();//это количество обновлений игрового цикла в герцах
	float sleepTime = 0;
	sf::Event event; //sfml класс событие, позволяет обрабатывать много чего, в данном случае я использую его для обработки закрытия окна
	float endCounter = 0;

	vector<sf::Glsl::Vec2> lightEmiters;

	sf::Shader shader;
	shader.loadFromFile("shaders/lightning.vert", "shaders/lightning.frag");

	//(*level.getCurrentShader()).second->setUniform("texture", sf::Shader::CurrentTexture);
	//(*level.getCurrentShader()).second->setUniform("resolution", sf::Glsl::Vec2(window.getSize().x, window.getSize().y));
	//(*level.getCurrentShader()).second->setUniform("ambientData", sf::Glsl::Vec4(0.5, 0.5, 0.8, 0.9));
	//(*level.getCurrentShader()).second->setUniform("lightData", sf::Glsl::Vec4(1.0, 0.5, 0.2, 2));
	//(*level.getCurrentShader()).second->setUniform("lightSize", sf::Glsl::Vec2(0.1, 0));

	shader.setUniform("texture", sf::Shader::CurrentTexture);
	shader.setUniform("resolution", sf::Glsl::Vec2(window.getSize().x, window.getSize().y));
	shader.setUniform("ambientData", sf::Glsl::Vec4(0.9, 0.9, 1, 2.5));
	shader.setUniform("lightData", sf::Glsl::Vec4(1.0, 0.5, 0.2, 2));
	shader.setUniform("lightSize", sf::Glsl::Vec2(0.15, 0));

	sf::FloatRect viewRect;//прямоугольник она для проверки, входит ли объекты в область видимости игрока(т.е. вида окна)

	Background background(0, 0, level.getResourceManager());
	while (window.isOpen())
	{
		while (window.pollEvent(event)) //обрабатываю закрытие окна
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();//чищу окно от прошлого кадра
		renderTexture.clear(/*sf::Color(12, 13, 69)*/);
	
		DebugInformation::getInstance().clear();

		viewRect = sf::FloatRect{ renderTexture.getView().getCenter().x - renderTexture.getView().getSize().x / 2, renderTexture.getView().getCenter().y - renderTexture.getView().getSize().y / 2, (float)renderTexture.getView().getSize().x, (float)renderTexture.getView().getSize().y };
		level.update(viewRect); //обновление 
		cam.update(1);
		interf.update(window.getView().getCenter().x, window.getView().getCenter().y); //вид окна - вид интерфеса. вид в cam - вид самой игры.(элементы окна рендерятся напрямую в окно, а остальное рендерится в renderTexture, а потом только в окно)
		background.update(viewRect);

		background.draw(renderTexture, viewRect);
		level.draw(renderTexture, lightEmiters, viewRect); //отрисовка


		if(lightEmiters.size() > 0){
			shader.setUniform("currentLightsCount", (int)lightEmiters.size());
			shader.setUniform("time", sf::Glsl::Vec2(0.5, 0));
			shader.setUniformArray("positions", lightEmiters.data(), (int)lightEmiters.size());
		}
		
		renderTexture.display();

		const sf::Texture& resultTexture = renderTexture.getTexture();
		sf::Sprite sp(resultTexture);

		window.draw(sp, &shader);
		//window.draw(sf::Sprite(resultTexture));
		

		interf.draw(window);
		window.display();
		lightEmiters.clear();

		if (level.isGameOver())
		{
			cam.deathcam();
			interf.gameover();
			endCounter++;
			if (endCounter > 200)
			{
				break;
			}
		}
		if (level.isLevelPassed())
		{
			cam.deathcam();
			interf.gamepassed();
			endCounter++;
			if (endCounter > 200)
			{
				break;
			}
		}
		nextUpdate += frameOffset;
		sleepTime = nextUpdate - updateClock.getElapsedTime().asMilliseconds();
		if(sleepTime >= 0)
		{
			sf::sleep(sf::milliseconds(sleepTime));
		}
	}
	return 0;
}
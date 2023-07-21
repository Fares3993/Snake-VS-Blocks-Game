#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Window.hpp>
#include<iostream>
#include<ctime>
#include<cstdlib>
#include<stdlib.h>
#include<sstream>
#include<fstream>
#include<string>

//**************namespace 
using namespace std;
using namespace sf;
/////////************** Function definitions
void game(RenderWindow &levelwindow);
void hardgame(RenderWindow &levelwindow);
void easygame(RenderWindow &levelwindow);
void fcis_window(RenderWindow &window);
void pause_window(RenderWindow &windowgame, RenderWindow &levelwindow);
void medgame(RenderWindow &levelwindow);
Text Transformation(int x);
void Results_window(RenderWindow &windowgame, RenderWindow &levelwindow, RenderWindow &window);
void levels(RenderWindow &window);
////****************** variables
int hiscore;
int score=0;
int check1 = -1;
int check2 = -1;
int check3 = -1;
int check4 = -1;
int checkf1 = -1;
int checkf2 = -1;
int countersnake;
int select_x, select_y;
int result;
bool movement = 1, checkmusic =1 ;
ifstream readfile("te.txt");
Music music1;
Music buttonsound;
RenderWindow window(VideoMode(600, 900), ("Snakes V.S Blocks"), Style::Close | Style::Resize);

int main()
{    
	
	
	///*********Music
	buttonsound.openFromFile("sound/button-sound.ogg");
	buttonsound.setVolume(20);

	music1.openFromFile("sound/game.ogg");
	music1.setLoop(true);
	music1.setVolume(20);


	//**font for all thing 
	Font font;
	font.loadFromFile("fonts/AGENCYB.ttf");

	//******* read fille
	
	readfile >> hiscore;
	readfile.read((char*)&hiscore, 1);

	//The first window of the game**

	
	RectangleShape background(Vector2f(600.0f, 900.0f));
	Texture image;
	image.loadFromFile("photo/snake vs blocks.png");
	background.setTexture(&image);


	Text text=Transformation(hiscore);
	text.setFont(font);
	text.setCharacterSize(70);
	text.setColor(Color::Black);
	text.setPosition(480, 370);
	


	while (window.isOpen())
	{

		Event event;
		while (window.pollEvent(event))
		{
			
			switch (event.type)
			{
			case Event::Closed:
				window.close();
				break;

			case Event::Resized:
				cout << "New window width" << event.size.width << endl;
				cout << "New window hight" << event.size.height << endl;
				break;

			case Event::TextEntered:
				if (event.text.unicode < 128)
					printf("%c", event.text.unicode);
				break;

			case Event::MouseButtonPressed:
				select_x = Mouse::getPosition().x;
				select_y = Mouse::getPosition().y;
				cout << "x=" << select_x << endl;
				cout << "y=" << select_y << endl;

				if ((select_x >= 705 && select_x <= 800) && (select_y >= 640 && select_y <= 745))
				{    
					buttonsound.play();
					cout << "Let's Play!" << endl;

					levels(window);
				}
				else if (select_x >= 815 && select_x <= 905 && select_y >= 640 && select_y <= 745)
				{ buttonsound.play();
					window.close();
				}
				else if (select_x >= 1030 && select_x <= 1115 && select_y >= 493 && select_y <= 600){
					buttonsound.play();
	
				}
				else if (select_x >= 860 && select_x <= 1080 && select_y >= 900 && select_y <= 997){
					cout << "Welcome To " << "<F C I S>" << endl;
					buttonsound.play();
					// FCIS windowteam  *

					fcis_window(window);
				}
				break;
			}
		}

		window.clear();
		window.draw(background);
		window.draw(text);
		window.display();
	}
	system("pause");
	return 0;
}

void levels(RenderWindow &window){
	RenderWindow levelwindow(VideoMode(600, 600), " levels window !");
	int x = 0;
	RectangleShape backgroundlevel(Vector2f(600.0f, 600.0f));
	Texture imagelevel;
	imagelevel.loadFromFile("photo/levelwindow.png");
	backgroundlevel.setTexture(&imagelevel);

	RectangleShape blocksound;
	blocksound.setSize(Vector2f(100, 10));
	blocksound.setFillColor(Color::Red);
	blocksound.setOutlineThickness(2);
	blocksound.setRotation(120);
	blocksound.setPosition(580, 500);

	while (levelwindow.isOpen()){

		Event event;

		while (levelwindow.pollEvent(event)){



			switch (event.type){
			case  Event::Closed:
				levelwindow.close();
				break;
			case Event::MouseButtonPressed:
				select_x = Mouse::getPosition().x;
				select_y = Mouse::getPosition().y;
				cout << " x = " << select_x << endl;
				cout << " y = " << select_y << endl;
				if (select_x >= 850 && select_x <= 1190 && select_y >= 340 && select_y <= 400){
					buttonsound.play();
					cout << " infinty level " << endl;
					if (checkmusic == 1)
						music1.play();
					   window.close();
					    game(levelwindow);


				}
				else if (select_x >= 695 && select_x <= 820 && select_y >= 540 && select_y <= 590){
					cout << " esay level " << endl;
					buttonsound.play();
					if (checkmusic == 1)
						music1.play();
					window.close();
					easygame(levelwindow);
				}
				else if (select_x >= 865 && select_x <= 1070 && select_y >= 550 && select_y <= 600){
					cout << " medium level " << endl;
					buttonsound.play();
					if (checkmusic == 1)
						music1.play();
					window.close();
					medgame(levelwindow);
				}
				else if (select_x >= 1115 && select_x <= 1250 && select_y >= 550 && select_y <= 600){
					cout << " hard level " << endl;
					buttonsound.play();
					if (checkmusic == 1)
						music1.play();
					window.close();
					hardgame(levelwindow);
				}
				else if (select_x >= 1166 && select_x <= 1260 && select_y >= 755 && select_y <= 865){
					cout << " sound button " << endl;
					buttonsound.play();
					if (x == 0){
						x = 1;
						checkmusic = 0;
					}
					else
					{
						checkmusic = 1;
						x = 0;
					}
				}

			}


		}
		levelwindow.clear();
		levelwindow.draw(backgroundlevel);
		if (x == 1){
			levelwindow.draw(blocksound);
		}
		levelwindow.display();
	}


}

void fcis_window(RenderWindow &window){

	sf::RenderWindow windowteam(VideoMode(600, 900), ("Snakes V.S Blocks"), Style::Close | Style::Resize);

	RectangleShape backgroundteam(Vector2f(600.0f, 900.0f));
	Texture imageteam;
	imageteam.loadFromFile("photo/fcis.png");
	backgroundteam.setTexture(&imageteam);

	float select_x, select_y;

	while (windowteam.isOpen())
	{
		Event event;
		while (windowteam.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				windowteam.close();
				break;

			case Event::Resized:
				cout << "New window width" << event.size.width << endl;
				cout << "New window hight" << event.size.height << endl;
				break;

			case Event::TextEntered:
				if (event.text.unicode < 128)
					printf("%c", event.text.unicode);
				break;

			case Event::MouseButtonPressed:
				select_x = Mouse::getPosition().x;
				select_y = Mouse::getPosition().y;

				if (select_x >= 1078 && select_x <= 1125 && select_y >= 910 && select_y <= 960){
					buttonsound.play();
					windowteam.close();
					window.close();
				}
				else if (select_x >= 1180 && select_x <= 1240 && select_y >= 807 && select_y <= 859){
					buttonsound.play(); 
					windowteam.close();
				}
				break;
			}
		}

		windowteam.clear();
		windowteam.draw(backgroundteam);
		windowteam.display();
	}
}

void pause_window(RenderWindow &windowgame, RenderWindow &levelwindow){


	RenderWindow windowpause(VideoMode(300, 400), "Snaks vs blocks");
	RectangleShape background_pause(Vector2f(300, 400));
	Texture image;
	image.loadFromFile("photo/pause.png ");
	background_pause.setTexture(&image);

	while (windowpause.isOpen())
	{
		Event event;
		while (windowpause.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				windowpause.close();
				break;
			case Event::Resized:
				cout << "new window width:" << event.size.width << endl;
				cout << "new window height:" << event.size.height << endl;
				break;
			case Event::MouseButtonPressed:
				select_x = Mouse::getPosition().x;
				select_y = Mouse::getPosition().y;
				cout << "x=" << select_x << endl;
				cout << "y=" << select_y << endl;
				if (select_x >= 920 && select_x <= 1012 && select_y >= 480 && select_y <= 532)
				{

					cout << "resume!";
					buttonsound.play();
					windowpause.close();
				
				}
				else if (select_x >= 920 && select_x <= 1012 && select_y >= 640 && select_y <= 695)
				{
					music1.stop();
					cout << "Exist!" << endl;
					buttonsound.play(); 
					windowpause.close();
					windowgame.close();
					levelwindow.close();
				}

				break;
			}
		}

		windowpause.draw(background_pause);
		windowpause.display();
	}

}


Text Transformation(int x){
	stringstream stream;
	stream << x;
	string string;
	stream >> string;

	sf::Text text;
	text.setString(string);
	return text;
}

void Results_window(RenderWindow &windowgame, RenderWindow &levelwindow, RenderWindow &window){

	windowgame.close();
	music1.stop();
	Music loser;
	loser.openFromFile("sound/lose.ogg");
	//*
	Music winner;
	winner.openFromFile("sound/win.ogg");
	Font font;
	font.loadFromFile("fonts/AGENCYB.ttf");
	//windowgame.close();
	//music.stop();windowgame.close();
							RenderWindow Result(VideoMode(600, 900), ("Snakes V.S Blocks Result"), Style::Close | Style::Resize);
							RectangleShape background(Vector2f(600, 900));
							Texture image1;
							image1.loadFromFile("photo/end game window.png");
							background.setTexture(&image1);
							//*
							sf::Texture lose;
							lose.loadFromFile("photo/lose.png");
							sf::Sprite sprite1;
							sprite1.setTexture(lose);
							sprite1.setPosition(sf::Vector2f(100, 20));
							sprite1.setScale(sf::Vector2f(0.6, 0.6));
							//**
							sf::Texture win;
							win.loadFromFile("photo/win.png");
							sf::Sprite sprite2;
							sprite2.setTexture(win);
							sprite2.setPosition(sf::Vector2f(100, -40));
							sprite2.setScale(sf::Vector2f(0.8, 0.8));

							//High Score of the game**
								readfile >> hiscore;
								readfile.read((char*)&hiscore, 1);
								if (score > hiscore)
								{
									hiscore = score;
									ofstream write("te.txt");
									write << hiscore;
									write.close();
									winner.setLoop(1000);
									winner.play();
								}
								else
								{
									loser.setLoop(1000);
									loser.play();

								}
							
							readfile.close();
							
							while (Result.isOpen())
							{

								Text text1 = Transformation(score);
								text1.setFont(font);
								text1.setCharacterSize(70);
								text1.setStyle(Text::Style::Bold | Text::Style::Italic);
								text1.setPosition(Vector2f(440, 380));
								text1.setFillColor(Color::Black);

								//**


								Text text2 = Transformation(hiscore);
								text2.setFont(font);
								text2.setCharacterSize(70);
								text2.setStyle(Text::Style::Bold | Text::Style::Italic);
								text2.setPosition(Vector2f(450, 500));
								text2.setFillColor(Color::Black);

								Event event;
								while (Result.pollEvent(event))
								{

									if (event.type == Event::Closed)
									{

										Result.close();
										//windowgame.close();
									}

									if (event.type == Event::MouseButtonPressed)
									{
										int select_x, select_y;
											select_x = Mouse::getPosition().x;
											select_y = Mouse::getPosition().y;

										if ((select_x >= 780 && select_x <= 950) && (select_y >= 830 && select_y <= 905))
										{
											cout << "Let's Play!" << endl;
											buttonsound.play(); 
											Result.close();
											countersnake = 40;
											score = 0;
											winner.stop();
											loser.stop();
											levels(window);

											
										}
										if ((select_x >= 1000 && select_x <= 1180) && (select_y >= 830 && select_y <= 905))
										{
											buttonsound.play();
											Result.close();

											windowgame.close();
											levelwindow.close();
										   	
										}


									}


								}




								Result.clear();

								Result.draw(background);

								if (hiscore>score)
								{

		                             Result.draw(sprite1);
								}
								else
								{

									Result.draw(sprite2);
								}
								Result.draw(text1);
								Result.draw(text2);
								Result.display();


							}
}


void game(RenderWindow &levelwindow){



	 countersnake = 40;

	//**font for all thing 
	Font font;
	font.loadFromFile("fonts/AGENCYB.ttf");


	//The apperance and dis apperance of blocks**

	int b1[300];
	int b2[300];
	int b3[300];
	int b4[300];
	for (int i = 0; i < 300; i++)
	{
		b1[i] = rand() % 7;
		b2[i] = rand() % 6;
		b3[i] = rand() % 7;
		b4[i] = rand() % 6;
	}


	// text on blocks && fruits**

	srand(time(NULL));
	int cou1[300];
	int cou2[300]; int cou3[300]; int cou4[300];
	for (int h = 0; h < 300; h++)
	{
		cou1[h] = 5 + rand() % 40;
		cou2[h] = 5 + rand() % 30;
		cou3[h] = 1 + rand() % 35;
		cou4[h] = 7 + rand() % 45;
	}

	int cou5 = 1 + rand() % 10;
	int cou6 = 1 + rand() % 15;


	// NUMBERS ON BLOCKS***
	Text text_counter1[300];
	Text text_counter2[300];
	Text text_counter3[300];
	Text text_counter4[300];
	for (int h = 0; h < 300; h++){

		text_counter1[h] = Transformation(cou1[h]);
		text_counter1[h].setCharacterSize(40);
		text_counter1[h].setFont(font);
		text_counter1[h].setColor(Color::Green);

		//**

		text_counter2[h] = Transformation(cou2[h]);
		text_counter2[h].setCharacterSize(40);
		text_counter2[h].setFont(font);
		text_counter2[h].setColor(Color::Green);

		//**
		text_counter3[h] = Transformation(cou3[h]);
		text_counter3[h].setCharacterSize(40);
		text_counter3[h].setFont(font);
		text_counter3[h].setColor(Color::Green);
		//**

		text_counter4[h] = Transformation(cou4[h]);
		text_counter4[h].setCharacterSize(40);
		text_counter4[h].setFont(font);
		text_counter4[h].setColor(Color::Green);

	}
	// NUMBERS ON fruitS***

	Text text_frcounter1 = Transformation(cou5);
	text_frcounter1.setCharacterSize(20);
	text_frcounter1.setFont(font);
	text_frcounter1.setColor(Color::Yellow);
	//**
	Text text_frcounter2 = Transformation(cou6);
	text_frcounter2.setCharacterSize(20);
	text_frcounter2.setFont(font);
	text_frcounter2.setColor(Color::Yellow);

	//	Window Game**
	//Drawing the background of the game***

	RenderWindow windowgame(sf::VideoMode(600, 900), ("snaks vs blocks"), Style::Close | Style::Resize);
	View view(windowgame.getDefaultView());
	FloatRect fbounds(0.0f, 0.0f, 600.0f, 50000.0f);
	Texture image;
	image.loadFromFile("photo/background.png");
	IntRect ibounds(fbounds);
	image.setRepeated(true);
	Sprite background(image, ibounds);
	background.setPosition(fbounds.left, fbounds.top - 50000.f + view.getSize().y);

	//Drawing array of Block1 && Block2 && Block3 && Block4 **	

	Texture texture1;
	texture1.loadFromFile("photo/blocks.png");
	int y1 = 1;
	Sprite block1[300];

	Texture texture2;
	texture2.loadFromFile("photo/blocks.png");
	int y2 = 1;
	Sprite block2[300];

	Texture texture3;
	texture3.loadFromFile("photo/blocks.png");
	int y3 = 1;
	Sprite block3[300];

	Texture texture4;
	texture4.loadFromFile("photo/blocks.png");
	int y4 = 1;
	Sprite block4[300];

	for (int i = 0; i < 300; i++)
	{
		//	if (draw1)
		{
			block1[i].setTexture(texture1);
			block1[i].setTextureRect(IntRect(0, 0, 120, 100));
			block1[i].setPosition(Vector2f(25, 100 * y1));
			y1 -= 7;
		}

		block2[i].setTexture(texture2);
		block2[i].setTextureRect(IntRect(0, 0, 120, 100));
		block2[i].setPosition(Vector2f(170, 100 * y2));
		y2 -= 7;

		block3[i].setTexture(texture3);
		block3[i].setTextureRect(IntRect(0, 0, 120, 100));
		block3[i].setPosition(Vector2f(315, 100 * y3));
		y3 -= 7;

		block4[i].setTexture(texture4);
		block4[i].setTextureRect(IntRect(0, 0, 120, 100));
		block4[i].setPosition(Vector2f(460, 100 * y4));
		y4 -= 7;
	}

	//Drawing fruits**
	//FRUIT1 && FRUIT2  **

	Texture texture5;
	texture5.loadFromFile("photo/DIAMOND.png");
	int y5 = 1;
	Sprite fruit1[300];

	Texture texture6;
	texture6.loadFromFile("photo/DIAMOND.png");
	int y6 = 1;
	Sprite fruit2[300];

	for (int i = 0; i < 300; i++){
		fruit1[i].setTexture(texture5);
		fruit1[i].setTextureRect(IntRect(0, 0, 30, 30));
		srand(time(NULL));
		fruit1[i].setPosition(Vector2f((rand() % 241) + 10, (rand() % 301 * y5) + 300 * y5));
		y5 -= 2;

		fruit2[i].setTexture(texture6);
		fruit2[i].setTextureRect(IntRect(0, 0, 30, 30));
		fruit2[i].setPosition(Vector2f((rand() % 271) + 260, (rand() % 301 * y6) + 300 * y6));
		y6 -= 2;
	}


	// 10:250  && 300:600 for fruit1 
	//260:530 && 300:600 for fruit2
	//**

	//Drawing the snake***
	Texture texture8;
	texture8.loadFromFile("photo/snake.png");
	texture8.setRepeated(true);
	Sprite player;
	player.setTexture(texture8);
	player.setPosition(Vector2f(300.0f, 750.0f));
	player.setScale(Vector2f(0.25, 0.25));
	Vector2<float>snakeSpeed(0, -7.0);

	//Drawing the tail***
	Texture tail;
	tail.loadFromFile("photo/tail.png");
	tail.setRepeated(true);
	Sprite t;
	t.setTexture(tail);
	t.setPosition(Vector2f(300.0f, 827));
	t.setScale(Vector2f(0.1, 0.1));
	Vector2<float>tailSpeed(0, -7.0);


	// PAUSE *

	Text pausemaek;
	pausemaek.setFont(font);
	pausemaek.setString("II");
	pausemaek.setCharacterSize(50);
	pausemaek.setStyle(Text::Style::Bold);
	pausemaek.setOrigin(25.0f, 50.0f);
	pausemaek.setPosition(Vector2f(600, 60));
	Vector2<float>pausemaekSpeed(0, -7.0);

	// SCORE *

	Text text1;
	text1.setFont(font);
	text1.setString("score: ");
	text1.setCharacterSize(40);
	text1.setStyle(Text::Style::Bold);
	text1.setOrigin(25.0f, 50.0f);
	text1.setPosition(Vector2f(30, 60));
	Vector2<float>text1Speed(0, -7.0);

	//COUNTER**

	Text text2;
	text2.setFont(font);
	text2.setString(" counter : ");
	text2.setCharacterSize(40);
	text2.setStyle(Text::Style::Bold);
	text2.setOrigin(25.0f, 50.0f);
	text2.setPosition(Vector2f(20, 90));
	Vector2<float>text2Speed(0, -7.0);

	//COUNTER snake** 
	stringstream ss;

	Text textcounter;
	textcounter.setFont(font);

	textcounter.setCharacterSize(40);
	textcounter.setStyle(Text::Style::Bold);
	textcounter.setOrigin(25.0f, 50.0f);
	textcounter.setPosition(Vector2f(180, 90));
	Vector2<float>textcounterSpeed(0, -7.0);


	//COUNTER score** 
	stringstream sss;

	Text textcounterscore;
	textcounterscore.setFont(font);

	textcounterscore.setCharacterSize(40);
	textcounterscore.setStyle(Text::Style::Bold);
	textcounterscore.setOrigin(25.0f, 50.0f);
	textcounterscore.setPosition(Vector2f(150, 60));
	Vector2<float>textcounterscoreSpeed(0, -7.0);

	//Window Game OOPEN **

	while (windowgame.isOpen())
	{
		ss.str("");
		ss << countersnake;
		textcounter.setString(ss.str());

		sss.str("");
		sss << score;
		textcounterscore.setString(sss.str());
		if (movement)
		{
			view.move(0.0f, -7.0f);
			pausemaek.move(pausemaekSpeed.x, pausemaekSpeed.y);
			text1.move(pausemaekSpeed.x, pausemaekSpeed.y);
			text2.move(pausemaekSpeed.x, pausemaekSpeed.y);
			textcounter.move(0.0f, -7.0f);
			textcounterscore.move(0.0f, -7.0f);
			player.move(snakeSpeed.x, snakeSpeed.y);
			t.move(tailSpeed.x, tailSpeed.y);
		}
		//music game**
		//	music1.play();
		//WINDOW PAUSE***

		if (select_x >= 1244 && select_x <= 1262 && select_y >= 145 && select_y <= 187)
		{
			pause_window(windowgame,levelwindow);

			

		}
		//Window Game Events***

		Event event;
		while (windowgame.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				windowgame.close();
				break;
			case Event::Resized:
				cout << "New window width" << event.size.width << endl;
				cout << "New window hight" << event.size.height << endl;
				break;

			case Event::MouseButtonPressed:
				select_x = Mouse::getPosition().x;
				select_y = Mouse::getPosition().y;
				cout << "x=" << select_x << endl;
				cout << "y=" << select_y << endl;

			case Event::TextEntered:
				if (event.text.unicode < 128)
					printf("%c", event.text.unicode);
				break;
			}
		}

		windowgame.setView(view);
		windowgame.clear();
		windowgame.draw(background);
		windowgame.draw(pausemaek);
		windowgame.draw(text1);
		windowgame.draw(text2);
		windowgame.draw(textcounter);
		windowgame.draw(textcounterscore);
		windowgame.draw(player);
		windowgame.draw(t);
		//***collision

		int i = 0;
		for (; i < 300; i++){

			movement = 1;


			if (b1[i] != 0)
			if (player.getGlobalBounds().intersects(block1[i].getGlobalBounds()))
			{
				countersnake = countersnake - cou1[i];
				
				result = cou1[i];
				score = score + result;
		
				while (1)
				{
					if (cou1[i] == 0)
					{
						check1 = i;
						break;
					}
					else{
						cou1[i] = cou1[i] - 1;
						text_counter1[i] = Transformation(cou1[i]);
						text_counter1[i].setFont(font);
						text_counter1[i].setColor(Color::Green);
						windowgame.draw(text_counter1[i]);
						movement = 0;
						
					}
				}
				break;
			}

			if (b4[i] != 0)
			if (player.getGlobalBounds().intersects(block4[i].getGlobalBounds()))
			{
				countersnake = countersnake - cou4[i];
				//cout << countersnake << endl;
				result = cou4[i];
				score = score + result;
			//	cout << score << endl;
				while (1)
				{
					if (cou4[i] == 0)
					{
						check4 = i;
						break;
					}
					else{
						cou4[i] = cou4[i] - 1;
						text_counter1[i] = Transformation(cou1[i]);
						text_counter1[i].setFont(font);
						text_counter1[i].setColor(Color::Green);
						windowgame.draw(text_counter1[i]);
						movement = 0;
						//		cout << cou4[i] << endl;
					}
				}
				break;
			}
			if (b2[i] != 0)
			if (player.getGlobalBounds().intersects(block2[i].getGlobalBounds()))
			{
				countersnake = countersnake - cou2[i];

				result = cou2[i];
				score = score + result;

				while (1)
				{
					if (cou2[i] == 0)
					{
						check2 = i;
						break;
					}
					else{
						cou2[i] = cou2[i] - 1;
						text_counter1[i] = Transformation(cou1[i]);
						text_counter1[i].setFont(font);
						text_counter1[i].setColor(Color::Green);
						windowgame.draw(text_counter1[i]);
						movement = 0;

					}
				}
				break;
			}


			if (b3[i] != 0)
			if (player.getGlobalBounds().intersects(block3[i].getGlobalBounds()))
			{
				countersnake = countersnake - cou3[i];

				result = cou3[i];
				score = score + result;
				//cout << score << endl;
				while (1)
				{
					if (cou3[i] == 0)
					{
						check3 = i;
						break;
					}
					else{
						cou3[i] = cou3[i] - 1;
						text_counter1[i] = Transformation(cou1[i]);
						text_counter1[i].setFont(font);
						text_counter1[i].setColor(Color::Green);
						windowgame.draw(text_counter1[i]);
						movement = 0;
					}
				}
				break;
			}




			if (player.getGlobalBounds().intersects(fruit1[i].getGlobalBounds()))
			{
				checkf1 = i;
				countersnake = countersnake + cou5;
				break;
			}
			if (player.getGlobalBounds().intersects(fruit2[i].getGlobalBounds()))
			{
				checkf2 = i;
				countersnake = countersnake + cou6;
				break;
			}
		}




		//*
		for (int i = 0; i < 300; i++)
		{

			if (checkf1 != i)
			{
				windowgame.draw(fruit1[i]);
				text_frcounter1.setPosition(Vector2f(fruit1[i].getPosition().x + 10, fruit1[i].getPosition().y - 20));
				windowgame.draw(text_frcounter1);
			}

			if (checkf2 != i){
				windowgame.draw(fruit2[i]);
				text_frcounter2.setPosition(Vector2f(fruit2[i].getPosition().x + 10, fruit2[i].getPosition().y - 20));
				windowgame.draw(text_frcounter2);
			}
		}

		//**

		for (int i = 0; i < 300; i++){
			if (b1[i]>0)
			if (check1 == i){ check1 = -1; }
			else
			{
				windowgame.draw(block1[i]);
				text_counter1[i].setPosition(Vector2f(block1[i].getPosition().x + 10, block1[i].getPosition().y + 10));
				windowgame.draw(text_counter1[i]);

			}



			if (b2[i] > 0)
			if (check2 == i){ check2 = -1; }
			else
			{
				windowgame.draw(block2[i]);
				text_counter2[i].setPosition(Vector2f(block2[i].getPosition().x + 10, block2[i].getPosition().y + 10));
				windowgame.draw(text_counter2[i]);

			}
			if (b3[i] > 0)
			if (check3 == i){ check3 = -1; }
			else
			{
				windowgame.draw(block3[i]);
				text_counter3[i].setPosition(Vector2f(block3[i].getPosition().x + 10, block3[i].getPosition().y + 10));
				windowgame.draw(text_counter3[i]);

			}

			if (b4[i] > 0)
			if (check4 == i){ check4 = -1; }
			else
			{
				windowgame.draw(block4[i]);
				text_counter4[i].setPosition(Vector2f(block4[i].getPosition().x + 10, block4[i].getPosition().y + 10));
				windowgame.draw(text_counter4[i]);

			}

		}
		windowgame.display();



		//Snake.Move***

		if (Keyboard::isKeyPressed(Keyboard::Key::Left) && player.getPosition().x > 0)
		{
			player.move(-4.0f, 0.0f);
			t.move(-4.0f, 0.0f);
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::Right) && player.getPosition().x < 550)
		{
			player.move(4.0f, 0.0f);
			t.move(4.0f, 0.0f);
		}


		if (countersnake < 0) {
			Results_window(windowgame, levelwindow, window);
			
			
		}


	}


}


void easygame(RenderWindow &levelwindow){


	 countersnake = 60;

	//**font for all thing 
	Font font;
	font.loadFromFile("fonts/AGENCYB.ttf");


	//The apperance and dis apperance of blocks**

	int b1[300];
	int b2[300];
	int b3[300];
	int b4[300];
	for (int i = 0; i < 300; i++)
	{
		b1[i] = rand() % 7;
		b2[i] = rand() % 6;
		b3[i] = rand() % 7;
		b4[i] = rand() % 6;
	}


	// text on blocks && fruits**

	srand(time(NULL));
	int cou1[300];
	int cou2[300]; int cou3[300]; int cou4[300];
	for (int h = 0; h < 300; h++)
	{
		cou1[h] = 5 + rand() % 20;
		cou2[h] = 5 + rand() % 15;
		cou3[h] = 1 + rand() % 10;
		cou4[h] = 7 + rand() % 15;
	}

	int cou5 = 1 + rand() % 10;
	int cou6 = 1 + rand() % 15;


	// NUMBERS ON BLOCKS***
	Text text_counter1[300];
	Text text_counter2[300];
	Text text_counter3[300];
	Text text_counter4[300];
	for (int h = 0; h < 300; h++){

		text_counter1[h] = Transformation(cou1[h]);
		text_counter1[h].setCharacterSize(40);
		text_counter1[h].setFont(font);
		text_counter1[h].setColor(Color::Green);

		//**

		text_counter2[h] = Transformation(cou2[h]);
		text_counter2[h].setCharacterSize(40);
		text_counter2[h].setFont(font);
		text_counter2[h].setColor(Color::Green);

		//**
		text_counter3[h] = Transformation(cou3[h]);
		text_counter3[h].setCharacterSize(40);
		text_counter3[h].setFont(font);
		text_counter3[h].setColor(Color::Green);
		//**

		text_counter4[h] = Transformation(cou4[h]);
		text_counter4[h].setCharacterSize(40);
		text_counter4[h].setFont(font);
		text_counter4[h].setColor(Color::Green);

	}
	// NUMBERS ON fruitS***

	Text text_frcounter1 = Transformation(cou5);
	text_frcounter1.setCharacterSize(20);
	text_frcounter1.setFont(font);
	text_frcounter1.setColor(Color::Yellow);
	//**
	Text text_frcounter2 = Transformation(cou6);
	text_frcounter2.setCharacterSize(20);
	text_frcounter2.setFont(font);
	text_frcounter2.setColor(Color::Yellow);

	//	Window Game**
	//Drawing the background of the game***

	RenderWindow windowgame(sf::VideoMode(600, 900), ("snaks vs blocks"), Style::Close | Style::Resize);
	View view(windowgame.getDefaultView());
	FloatRect fbounds(0.0f, 0.0f, 600.0f, 50000.0f);
	Texture image;
	image.loadFromFile("photo/background.png");
	IntRect ibounds(fbounds);
	image.setRepeated(true);
	Sprite background(image, ibounds);
	background.setPosition(fbounds.left, fbounds.top - 50000.f + view.getSize().y);

	//Drawing array of Block1 && Block2 && Block3 && Block4 **	

	Texture texture1;
	texture1.loadFromFile("photo/blocks.png");
	int y1 = 1;
	Sprite block1[300];

	Texture texture2;
	texture2.loadFromFile("photo/blocks.png");
	int y2 = 1;
	Sprite block2[300];

	Texture texture3;
	texture3.loadFromFile("photo/blocks.png");
	int y3 = 1;
	Sprite block3[300];

	Texture texture4;
	texture4.loadFromFile("photo/blocks.png");
	int y4 = 1;
	Sprite block4[300];

	for (int i = 0; i < 300; i++)
	{
		//	if (draw1)
		{
			block1[i].setTexture(texture1);
			block1[i].setTextureRect(IntRect(0, 0, 120, 100));
			block1[i].setPosition(Vector2f(25, 100 * y1));
			y1 -= 7;
		}

		block2[i].setTexture(texture2);
		block2[i].setTextureRect(IntRect(0, 0, 120, 100));
		block2[i].setPosition(Vector2f(170, 100 * y2));
		y2 -= 7;

		block3[i].setTexture(texture3);
		block3[i].setTextureRect(IntRect(0, 0, 120, 100));
		block3[i].setPosition(Vector2f(315, 100 * y3));
		y3 -= 7;

		block4[i].setTexture(texture4);
		block4[i].setTextureRect(IntRect(0, 0, 120, 100));
		block4[i].setPosition(Vector2f(460, 100 * y4));
		y4 -= 7;
	}

	//Drawing fruits**
	//FRUIT1 && FRUIT2  **

	Texture texture5;
	texture5.loadFromFile("photo/DIAMOND.png");
	int y5 = 1;
	Sprite fruit1[300];

	Texture texture6;
	texture6.loadFromFile("photo/DIAMOND.png");
	int y6 = 1;
	Sprite fruit2[300];

	for (int i = 0; i < 300; i++){
		fruit1[i].setTexture(texture5);
		fruit1[i].setTextureRect(IntRect(0, 0, 30, 30));
		srand(time(NULL));
		fruit1[i].setPosition(Vector2f((rand() % 241) + 10, (rand() % 301 * y5) + 300 * y5));
		y5 -= 2;

		fruit2[i].setTexture(texture6);
		fruit2[i].setTextureRect(IntRect(0, 0, 30, 30));
		fruit2[i].setPosition(Vector2f((rand() % 271) + 260, (rand() % 301 * y6) + 300 * y6));
		y6 -= 2;
	}
	// 10:250  && 300:600 for fruit1 
	//260:530 && 300:600 for fruit2
	//**

	//Drawing the snake***
	Texture texture8;
	texture8.loadFromFile("photo/snake.png");
	texture8.setRepeated(true);
	Sprite player;
	player.setTexture(texture8);
	player.setPosition(Vector2f(300.0f, 750.0f));
	player.setScale(Vector2f(0.25, 0.25));
	Vector2<float>snakeSpeed(0, -7.0);

	//Drawing the tail***
	Texture tail;
	tail.loadFromFile("photo/tail.png");
	tail.setRepeated(true);
	Sprite t;
	t.setTexture(tail);
	t.setPosition(Vector2f(300.0f, 827));
	t.setScale(Vector2f(0.1, 0.1));
	Vector2<float>tailSpeed(0, -7.0);


	// PAUSE *

	Text pausemaek;
	pausemaek.setFont(font);
	pausemaek.setString("II");
	pausemaek.setCharacterSize(50);
	pausemaek.setStyle(Text::Style::Bold);
	pausemaek.setOrigin(25.0f, 50.0f);
	pausemaek.setPosition(Vector2f(600, 60));
	Vector2<float>pausemaekSpeed(0, -7.0);

	// SCORE *

	Text text1;
	text1.setFont(font);
	text1.setString("score: ");
	text1.setCharacterSize(40);
	text1.setStyle(Text::Style::Bold);
	text1.setOrigin(25.0f, 50.0f);
	text1.setPosition(Vector2f(30, 60));
	Vector2<float>text1Speed(0, -7.0);

	//COUNTER**

	Text text2;
	text2.setFont(font);
	text2.setString(" counter : ");
	text2.setCharacterSize(40);
	text2.setStyle(Text::Style::Bold);
	text2.setOrigin(25.0f, 50.0f);
	text2.setPosition(Vector2f(20, 90));
	Vector2<float>text2Speed(0, -7.0);

	//COUNTER snake** 
	stringstream ss;

	Text textcounter;
	textcounter.setFont(font);

	textcounter.setCharacterSize(40);
	textcounter.setStyle(Text::Style::Bold);
	textcounter.setOrigin(25.0f, 50.0f);
	textcounter.setPosition(Vector2f(180, 90));
	Vector2<float>textcounterSpeed(0, -7.0);


	//COUNTER score** 
	stringstream sss;

	Text textcounterscore;
	textcounterscore.setFont(font);

	textcounterscore.setCharacterSize(40);
	textcounterscore.setStyle(Text::Style::Bold);
	textcounterscore.setOrigin(25.0f, 50.0f);
	textcounterscore.setPosition(Vector2f(150, 60));
	Vector2<float>textcounterscoreSpeed(0, -7.0);

	//Window Game OOPEN **

	while (windowgame.isOpen())
	{
		ss.str("");
		ss << countersnake;
		textcounter.setString(ss.str());

		sss.str("");
		sss << score;
		textcounterscore.setString(sss.str());
		if (movement)
		{
			view.move(0.0f, -7.0f);
			pausemaek.move(pausemaekSpeed.x, pausemaekSpeed.y);
			text1.move(pausemaekSpeed.x, pausemaekSpeed.y);
			text2.move(pausemaekSpeed.x, pausemaekSpeed.y);
			textcounter.move(0.0f, -7.0f);
			textcounterscore.move(0.0f, -7.0f);
			player.move(snakeSpeed.x, snakeSpeed.y);
			t.move(tailSpeed.x, tailSpeed.y);
		}
		//music game**

		//**

		//WINDOW PAUSE***

		if (select_x >= 1244 && select_x <= 1262 && select_y >= 145 && select_y <= 187)
		{
			pause_window(windowgame, levelwindow);
				
			
		}
		//Window Game Events***

		Event event;
		while (windowgame.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				windowgame.close();
				break;
			case Event::Resized:
				cout << "New window width" << event.size.width << endl;
				cout << "New window hight" << event.size.height << endl;
				break;

			case Event::MouseButtonPressed:
				select_x = Mouse::getPosition().x;
				select_y = Mouse::getPosition().y;

			case Event::TextEntered:
				if (event.text.unicode < 128)
					printf("%c", event.text.unicode);
				break;
			}
		}

		windowgame.setView(view);
		windowgame.clear();
		windowgame.draw(background);
		windowgame.draw(pausemaek);
		windowgame.draw(text1);
		windowgame.draw(text2);
		windowgame.draw(textcounter);
		windowgame.draw(textcounterscore);
		windowgame.draw(player);
		windowgame.draw(t);
		//***collision

		int i = 0;
		for (; i < 300; i++){

			movement = 1;


			if (b1[i] != 0)
			if (player.getGlobalBounds().intersects(block1[i].getGlobalBounds()))
			{
				countersnake = countersnake - cou1[i];
				//cout << countersnake << endl;
				result = cou1[i];
				score = score + result;
				//cout << score << endl;
				while (1)
				{
					if (cou1[i] == 0)
					{
						check1 = i;
						break;
					}
					else{
						cou1[i] = cou1[i] - 1;
						text_counter1[i] = Transformation(cou1[i]);
						text_counter1[i].setFont(font);
						text_counter1[i].setColor(Color::Green);
						windowgame.draw(text_counter1[i]);
						movement = 0;
						//cout << cou1[i] << endl;
					}
				}
				break;
			}

			if (b4[i] != 0)
			if (player.getGlobalBounds().intersects(block4[i].getGlobalBounds()))
			{
				countersnake = countersnake - cou4[i];
				//cout << countersnake << endl;
				result = cou4[i];
				score = score + result;
				//cout << score << endl;
				while (1)
				{
					if (cou4[i] == 0)
					{
						check4 = i;
						break;
					}
					else{
						cou4[i] = cou4[i] - 1;
						text_counter1[i] = Transformation(cou1[i]);
						text_counter1[i].setFont(font);
						text_counter1[i].setColor(Color::Green);
						windowgame.draw(text_counter1[i]);
						movement = 0;
						//		cout << cou4[i] << endl;
					}
				}
				break;
			}
			if (b2[i] != 0)
			if (player.getGlobalBounds().intersects(block2[i].getGlobalBounds()))
			{
				countersnake = countersnake - cou2[i];

				result = cou2[i];
				score = score + result;

				while (1)
				{
					if (cou2[i] == 0)
					{
						check2 = i;
						break;
					}
					else{
						cou2[i] = cou2[i] - 1;
						text_counter1[i] = Transformation(cou1[i]);
						text_counter1[i].setFont(font);
						text_counter1[i].setColor(Color::Green);
						windowgame.draw(text_counter1[i]);
						movement = 0;

					}
				}
				break;
			}


			if (b3[i] != 0)
			if (player.getGlobalBounds().intersects(block3[i].getGlobalBounds()))
			{
				countersnake = countersnake - cou3[i];

				result = cou3[i];
				score = score + result;
				//cout << score << endl;
				while (1)
				{
					if (cou3[i] == 0)
					{
						check3 = i;
						break;
					}
					else{
						cou3[i] = cou3[i] - 1;
						text_counter1[i] = Transformation(cou1[i]);
						text_counter1[i].setFont(font);
						text_counter1[i].setColor(Color::Green);
						windowgame.draw(text_counter1[i]);
						movement = 0;
					}
				}
				break;
			}




			if (player.getGlobalBounds().intersects(fruit1[i].getGlobalBounds()))
			{
				checkf1 = i;
				countersnake = countersnake + cou5;
				break;
			}
			if (player.getGlobalBounds().intersects(fruit2[i].getGlobalBounds()))
			{
				checkf2 = i;
				countersnake = countersnake + cou6;
				break;
			}
		}




		//*
		for (int i = 0; i < 300; i++)
		{

			if (checkf1 != i)
			{
				windowgame.draw(fruit1[i]);
				text_frcounter1.setPosition(Vector2f(fruit1[i].getPosition().x + 10, fruit1[i].getPosition().y - 20));
				windowgame.draw(text_frcounter1);
			}

			if (checkf2 != i){
				windowgame.draw(fruit2[i]);
				text_frcounter2.setPosition(Vector2f(fruit2[i].getPosition().x + 10, fruit2[i].getPosition().y - 20));
				windowgame.draw(text_frcounter2);
			}
		}

		//**

		for (int i = 0; i < 300; i++){
			if (b1[i]>0)
			if (check1 == i){ check1 = -1; }
			else
			{
				windowgame.draw(block1[i]);
				text_counter1[i].setPosition(Vector2f(block1[i].getPosition().x + 10, block1[i].getPosition().y + 10));
				windowgame.draw(text_counter1[i]);

			}



			if (b2[i] > 0)
			if (check2 == i){ check2 = -1; }
			else
			{
				windowgame.draw(block2[i]);
				text_counter2[i].setPosition(Vector2f(block2[i].getPosition().x + 10, block2[i].getPosition().y + 10));
				windowgame.draw(text_counter2[i]);

			}
			if (b3[i] > 0)
			if (check3 == i){ check3 = -1; }
			else
			{
				windowgame.draw(block3[i]);
				text_counter3[i].setPosition(Vector2f(block3[i].getPosition().x + 10, block3[i].getPosition().y + 10));
				windowgame.draw(text_counter3[i]);

			}

			if (b4[i] > 0)
			if (check4 == i){ check4 = -1; }
			else
			{
				windowgame.draw(block4[i]);
				text_counter4[i].setPosition(Vector2f(block4[i].getPosition().x + 10, block4[i].getPosition().y + 10));
				windowgame.draw(text_counter4[i]);

			}

		}
		windowgame.display();



		//Snake.Move***

		if (Keyboard::isKeyPressed(Keyboard::Key::Left) && player.getPosition().x > 0)
		{
			player.move(-4.0f, 0.0f);
			t.move(-4.0f, 0.0f);
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::Right) && player.getPosition().x < 550)
		{
			player.move(4.0f, 0.0f);
			t.move(4.0f, 0.0f);
		}


		if (countersnake < 0) {
			Results_window(windowgame,levelwindow,window);
		}


	}
	}



void hardgame(RenderWindow &levelwindow){


	 countersnake = 30;

	//**font for all thing 
	Font font;
	font.loadFromFile("fonts/AGENCYB.ttf");


	//The apperance and dis apperance of blocks**

	int b1[300];
	int b2[300];
	for (int i = 0; i < 300; i++)
	{
		b1[i] = rand() % 7;
		b2[i] = rand() % 6;
			}


	// text on blocks && fruits**

	srand(time(NULL));
	int cou1[300];
	int cou2[300]; int cou3[300]; int cou4[300];
	
	for (int h = 0; h < 300; h++)
	{
		cou1[h] = 15 + rand() % 50;
		cou2[h] = 17 + rand() % 55;
		cou3[h] = 19 + rand() % 60;
		cou4[h] = 20 + rand() % 65;
	}

	int cou5 = 2 + rand() % 4;
	int cou6 = 3 + rand() % 5;


	// NUMBERS ON BLOCKS***
	Text text_counter1[300];
	Text text_counter2[300];
	Text text_counter3[300];
	Text text_counter4[300];
	for (int h = 0; h < 300; h++){

		text_counter1[h] = Transformation(cou1[h]);
		text_counter1[h].setCharacterSize(40);
		text_counter1[h].setFont(font);
		text_counter1[h].setColor(Color::Green);

		//**

		text_counter2[h] = Transformation(cou2[h]);
		text_counter2[h].setCharacterSize(40);
		text_counter2[h].setFont(font);
		text_counter2[h].setColor(Color::Green);

		//**
		text_counter3[h] = Transformation(cou3[h]);
		text_counter3[h].setCharacterSize(40);
		text_counter3[h].setFont(font);
		text_counter3[h].setColor(Color::Green);
		//**

		text_counter4[h] = Transformation(cou4[h]);
		text_counter4[h].setCharacterSize(40);
		text_counter4[h].setFont(font);
		text_counter4[h].setColor(Color::Green);

	}
	// NUMBERS ON fruitS***

	Text text_frcounter1 = Transformation(cou5);
	text_frcounter1.setCharacterSize(20);
	text_frcounter1.setFont(font);
	text_frcounter1.setColor(Color::Yellow);
	//**
	Text text_frcounter2 = Transformation(cou6);
	text_frcounter2.setCharacterSize(20);
	text_frcounter2.setFont(font);
	text_frcounter2.setColor(Color::Yellow);

	//	Window Game**
	//Drawing the background of the game***

	RenderWindow windowgame(sf::VideoMode(600, 900), ("snaks vs blocks"), Style::Close | Style::Resize);
	View view(windowgame.getDefaultView());
	FloatRect fbounds(0.0f, 0.0f, 600.0f, 50000.0f);
	Texture image;
	image.loadFromFile("photo/background.png");
	IntRect ibounds(fbounds);
	image.setRepeated(true);
	Sprite background(image, ibounds);
	background.setPosition(fbounds.left, fbounds.top - 50000.f + view.getSize().y);

	//Drawing array of Block1 && Block2 && Block3 && Block4 **	

	Texture texture1;
	texture1.loadFromFile("photo/blocks.png");
	int y1 = 1;
	Sprite block1[300];

	Texture texture2;
	texture2.loadFromFile("photo/blocks.png");
	int y2 = 1;
	Sprite block2[300];

	Texture texture3;
	texture3.loadFromFile("photo/blocks.png");
	int y3 = 1;
	Sprite block3[300];

	Texture texture4;
	texture4.loadFromFile("photo/blocks.png");
	int y4 = 1;
	Sprite block4[300];

	for (int i = 0; i < 300; i++)
	{
		//	if (draw1)
		{
			block1[i].setTexture(texture1);
			block1[i].setTextureRect(IntRect(0, 0, 120, 100));
			block1[i].setPosition(Vector2f(25, 100 * y1));
			y1 -= 7;
		}

		block2[i].setTexture(texture2);
		block2[i].setTextureRect(IntRect(0, 0, 120, 100));
		block2[i].setPosition(Vector2f(170, 100 * y2));
		y2 -= 7;

		block3[i].setTexture(texture3);
		block3[i].setTextureRect(IntRect(0, 0, 120, 100));
		block3[i].setPosition(Vector2f(315, 100 * y3));
		y3 -= 7;

		block4[i].setTexture(texture4);
		block4[i].setTextureRect(IntRect(0, 0, 120, 100));
		block4[i].setPosition(Vector2f(460, 100 * y4));
		y4 -= 7;
	}

	//Drawing fruits**
	//FRUIT1 && FRUIT2  **

	Texture texture5;
	texture5.loadFromFile("photo/DIAMOND.png");
	int y5 = 1;
	Sprite fruit1[300];

	Texture texture6;
	texture6.loadFromFile("photo/DIAMOND.png");
	int y6 = 1;
	Sprite fruit2[300];

	for (int i = 0; i < 300; i++){
		fruit1[i].setTexture(texture5);
		fruit1[i].setTextureRect(IntRect(0, 0, 30, 30));
		srand(time(NULL));
		fruit1[i].setPosition(Vector2f((rand() % 241) + 10, (rand() % 301 * y5) + 300 * y5));
		y5 -= 2;

		fruit2[i].setTexture(texture6);
		fruit2[i].setTextureRect(IntRect(0, 0, 30, 30));
		fruit2[i].setPosition(Vector2f((rand() % 271) + 260, (rand() % 301 * y6) + 300 * y6));
		y6 -= 2;
	}
	// 10:250  && 300:600 for fruit1 
	//260:530 && 300:600 for fruit2
	//**

	//Drawing the snake***
	Texture texture8;
	texture8.loadFromFile("photo/snake.png");
	texture8.setRepeated(true);
	Sprite player;
	player.setTexture(texture8);
	player.setPosition(Vector2f(300.0f, 750.0f));
	player.setScale(Vector2f(0.25, 0.25));
	Vector2<float>snakeSpeed(0, -7.0);

	//Drawing the tail***
	Texture tail;
	tail.loadFromFile("photo/tail.png");
	tail.setRepeated(true);
	Sprite t;
	t.setTexture(tail);
	t.setPosition(Vector2f(300.0f, 827));
	t.setScale(Vector2f(0.1, 0.1));
	Vector2<float>tailSpeed(0, -7.0);


	// PAUSE *

	Text pausemaek;
	pausemaek.setFont(font);
	pausemaek.setString("II");
	pausemaek.setCharacterSize(50);
	pausemaek.setStyle(Text::Style::Bold);
	pausemaek.setOrigin(25.0f, 50.0f);
	pausemaek.setPosition(Vector2f(600, 60));
	Vector2<float>pausemaekSpeed(0, -7.0);

	// SCORE *

	Text text1;
	text1.setFont(font);
	text1.setString("score: ");
	text1.setCharacterSize(40);
	text1.setStyle(Text::Style::Bold);
	text1.setOrigin(25.0f, 50.0f);
	text1.setPosition(Vector2f(30, 60));
	Vector2<float>text1Speed(0, -7.0);

	//COUNTER**

	Text text2;
	text2.setFont(font);
	text2.setString(" counter : ");
	text2.setCharacterSize(40);
	text2.setStyle(Text::Style::Bold);
	text2.setOrigin(25.0f, 50.0f);
	text2.setPosition(Vector2f(20, 90));
	Vector2<float>text2Speed(0, -7.0);

	//COUNTER snake** 
	stringstream ss;

	Text textcounter;
	textcounter.setFont(font);

	textcounter.setCharacterSize(40);
	textcounter.setStyle(Text::Style::Bold);
	textcounter.setOrigin(25.0f, 50.0f);
	textcounter.setPosition(Vector2f(180, 90));
	Vector2<float>textcounterSpeed(0, -7.0);


	//COUNTER score** 
	stringstream sss;

	Text textcounterscore;
	textcounterscore.setFont(font);

	textcounterscore.setCharacterSize(40);
	textcounterscore.setStyle(Text::Style::Bold);
	textcounterscore.setOrigin(25.0f, 50.0f);
	textcounterscore.setPosition(Vector2f(150, 60));
	Vector2<float>textcounterscoreSpeed(0, -7.0);

	//Window Game OOPEN **

	while (windowgame.isOpen())
	{
		ss.str("");
		ss << countersnake;
		textcounter.setString(ss.str());

		sss.str("");
		sss << score;
		textcounterscore.setString(sss.str());
		if (movement)
		{
			view.move(0.0f, -7.0f);
			pausemaek.move(pausemaekSpeed.x, pausemaekSpeed.y);
			text1.move(pausemaekSpeed.x, pausemaekSpeed.y);
			text2.move(pausemaekSpeed.x, pausemaekSpeed.y);
			textcounter.move(0.0f, -7.0f);
			textcounterscore.move(0.0f, -7.0f);
			player.move(snakeSpeed.x, snakeSpeed.y);
			t.move(tailSpeed.x, tailSpeed.y);
		}
		//music game**

		//**

		//WINDOW PAUSE***

		if (select_x >= 1244 && select_x <= 1262 && select_y >= 145 && select_y <= 187)
		{
			pause_window(windowgame, levelwindow);

		}
		//Window Game Events***

		Event event;
		while (windowgame.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				windowgame.close();
				break;
			case Event::Resized:
				cout << "New window width" << event.size.width << endl;
				cout << "New window hight" << event.size.height << endl;
				break;

			case Event::MouseButtonPressed:
				select_x = Mouse::getPosition().x;
				select_y = Mouse::getPosition().y;
				//cout << "x=" << select_x << endl;
				 //cout << "y=" << select_y << endl;

			case Event::TextEntered:
				if (event.text.unicode < 128)
					printf("%c", event.text.unicode);
				break;
			}
		}

		windowgame.setView(view);
		windowgame.clear();
		windowgame.draw(background);
		windowgame.draw(pausemaek);
		windowgame.draw(text1);
		windowgame.draw(text2);
		windowgame.draw(textcounter);
		windowgame.draw(textcounterscore);
		windowgame.draw(player);
		windowgame.draw(t);
		//***collision

		int i = 0;
		for (; i < 300; i++){

			movement = 1;


			if (b1[i] != 0)
			if (player.getGlobalBounds().intersects(block1[i].getGlobalBounds()))
			{
				countersnake = countersnake - cou1[i];
				//cout << countersnake << endl;
				result = cou1[i];
				score = score + result;
			//	cout << score << endl;
				while (1)
				{
					if (cou1[i] == 0)
					{
						check1 = i;
						break;
					}
					else{
						cou1[i] = cou1[i] - 1;
						text_counter1[i] = Transformation(cou1[i]);
						text_counter1[i].setFont(font);
						text_counter1[i].setColor(Color::Green);
						windowgame.draw(text_counter1[i]);
						movement = 0;
						//cout << cou1[i] << endl;
					}
				}
				break;
			}

			
			if (player.getGlobalBounds().intersects(block4[i].getGlobalBounds()))
			{
				countersnake = countersnake - cou4[i];
				//cout << countersnake << endl;
				result = cou4[i];
				score = score + result;
				//cout << score << endl;
				while (1)
				{
					if (cou4[i] == 0)
					{
						check4 = i;
						break;
					}
					else{
						cou4[i] = cou4[i] - 1;
						text_counter1[i] = Transformation(cou1[i]);
						text_counter1[i].setFont(font);
						text_counter1[i].setColor(Color::Green);
						windowgame.draw(text_counter1[i]);
						movement = 0;
						//		cout << cou4[i] << endl;
					}
				}
				break;
			}
			if (b2[i] != 0)
			if (player.getGlobalBounds().intersects(block2[i].getGlobalBounds()))
			{
				countersnake = countersnake - cou2[i];

				result = cou2[i];
				score = score + result;

				while (1)
				{
					if (cou2[i] == 0)
					{
						check2 = i;
						break;
					}
					else{
						cou2[i] = cou2[i] - 1;
						text_counter1[i] = Transformation(cou1[i]);
						text_counter1[i].setFont(font);
						text_counter1[i].setColor(Color::Green);
						windowgame.draw(text_counter1[i]);
						movement = 0;

					}
				}
				break;
			}
			if (player.getGlobalBounds().intersects(block3[i].getGlobalBounds()))
			{
				countersnake = countersnake - cou3[i];

				result = cou3[i];
				score = score + result;
				//cout << score << endl;
				while (1)
				{
					if (cou3[i] == 0)
					{
						check3 = i;
						break;
					}
					else{
						cou3[i] = cou3[i] - 1;
						text_counter1[i] = Transformation(cou1[i]);
						text_counter1[i].setFont(font);
						text_counter1[i].setColor(Color::Green);
						windowgame.draw(text_counter1[i]);
						movement = 0;
					}
				}
				break;
			}




			if (player.getGlobalBounds().intersects(fruit1[i].getGlobalBounds()))
			{
				checkf1 = i;
				countersnake = countersnake + cou5;
				break;
			}
			if (player.getGlobalBounds().intersects(fruit2[i].getGlobalBounds()))
			{
				checkf2 = i;
				countersnake = countersnake + cou6;
				break;
			}
		}




		//*
		for (int i = 0; i < 300; i++)
		{

			if (checkf1 != i)
			{
				windowgame.draw(fruit1[i]);
				text_frcounter1.setPosition(Vector2f(fruit1[i].getPosition().x + 10, fruit1[i].getPosition().y - 20));
				windowgame.draw(text_frcounter1);
			}

			if (checkf2 != i){
				windowgame.draw(fruit2[i]);
				text_frcounter2.setPosition(Vector2f(fruit2[i].getPosition().x + 10, fruit2[i].getPosition().y - 20));
				windowgame.draw(text_frcounter2);
			}
		}

		//**

		for (int i = 0; i < 300; i++){
			if (b1[i]>0)
			if (check1 == i){ check1 = -1; }
			else
			{
				windowgame.draw(block1[i]);
				text_counter1[i].setPosition(Vector2f(block1[i].getPosition().x + 10, block1[i].getPosition().y + 10));
				windowgame.draw(text_counter1[i]);

			}



			if (b2[i] > 0)
			if (check2 == i){ check2 = -1; }
			else
			{
				windowgame.draw(block2[i]);
				text_counter2[i].setPosition(Vector2f(block2[i].getPosition().x + 10, block2[i].getPosition().y + 10));
				windowgame.draw(text_counter2[i]);

			}
			
			if (check3 == i){ check3 = -1; }
			else
			{
				windowgame.draw(block3[i]);
				text_counter3[i].setPosition(Vector2f(block3[i].getPosition().x + 10, block3[i].getPosition().y + 10));
				windowgame.draw(text_counter3[i]);

			}

			if (check4 == i){ check4 = -1; }
			else
			{
				windowgame.draw(block4[i]);
				text_counter4[i].setPosition(Vector2f(block4[i].getPosition().x + 10, block4[i].getPosition().y + 10));
				windowgame.draw(text_counter4[i]);

			}

		}
		windowgame.display();



		//Snake.Move***

		if (Keyboard::isKeyPressed(Keyboard::Key::Left) && player.getPosition().x > 0)
		{
			player.move(-4.0f, 0.0f);
			t.move(-4.0f, 0.0f);
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::Right) && player.getPosition().x < 550)
		{
			player.move(4.0f, 0.0f);
			t.move(4.0f, 0.0f);
		}


		if (countersnake < 0) {
			Results_window(windowgame, levelwindow, window);
			
		}


	}


}


void medgame(RenderWindow &levelwindow){

	 countersnake = 40;

	//**font for all thing 
	Font font;
	font.loadFromFile("fonts/AGENCYB.ttf");


	//The apperance and dis apperance of blocks**

	int b1[300];
	int b2[300];
	int b3[300];
	int b4[300];
	for (int i = 0; i < 300; i++)
	{
		b1[i] = rand() % 7;
		b2[i] = rand() % 6;
		b3[i] = rand() % 7;
		b4[i] = rand() % 6;
	}


	// text on blocks && fruits**

	srand(time(NULL));
	int cou1[300];
	int cou2[300]; int cou3[300]; int cou4[300];
	for (int h = 0; h < 300; h++)
	{
		cou1[h] = 5 + rand() % 40;
		cou2[h] = 5 + rand() % 30;
		cou3[h] = 1 + rand() % 35;
		cou4[h] = 7 + rand() % 45;
	}

	int cou5 = 1 + rand() % 10;
	int cou6 = 1 + rand() % 15;


	// NUMBERS ON BLOCKS***
	Text text_counter1[300];
	Text text_counter2[300];
	Text text_counter3[300];
	Text text_counter4[300];
	for (int h = 0; h < 300; h++){

		text_counter1[h] = Transformation(cou1[h]);
		text_counter1[h].setCharacterSize(40);
		text_counter1[h].setFont(font);
		text_counter1[h].setColor(Color::Green);

		//**

		text_counter2[h] = Transformation(cou2[h]);
		text_counter2[h].setCharacterSize(40);
		text_counter2[h].setFont(font);
		text_counter2[h].setColor(Color::Green);

		//**
		text_counter3[h] = Transformation(cou3[h]);
		text_counter3[h].setCharacterSize(40);
		text_counter3[h].setFont(font);
		text_counter3[h].setColor(Color::Green);
		//**

		text_counter4[h] = Transformation(cou4[h]);
		text_counter4[h].setCharacterSize(40);
		text_counter4[h].setFont(font);
		text_counter4[h].setColor(Color::Green);

	}
	// NUMBERS ON fruitS***

	Text text_frcounter1 = Transformation(cou5);
	text_frcounter1.setCharacterSize(20);
	text_frcounter1.setFont(font);
	text_frcounter1.setColor(Color::Yellow);
	//**
	Text text_frcounter2 = Transformation(cou6);
	text_frcounter2.setCharacterSize(20);
	text_frcounter2.setFont(font);
	text_frcounter2.setColor(Color::Yellow);

	//	Window Game**
	//Drawing the background of the game***

	RenderWindow windowgame(sf::VideoMode(600, 900), ("snaks vs blocks"), Style::Close | Style::Resize);
	View view(windowgame.getDefaultView());
	FloatRect fbounds(0.0f, 0.0f, 600.0f, 50000.0f);
	Texture image;
	image.loadFromFile("photo/background.png");
	IntRect ibounds(fbounds);
	image.setRepeated(true);
	Sprite background(image, ibounds);
	background.setPosition(fbounds.left, fbounds.top - 50000.f + view.getSize().y);

	//Drawing array of Block1 && Block2 && Block3 && Block4 **	

	Texture texture1;
	texture1.loadFromFile("photo/blocks.png");
	int y1 = 1;
	Sprite block1[300];

	Texture texture2;
	texture2.loadFromFile("photo/blocks.png");
	int y2 = 1;
	Sprite block2[300];

	Texture texture3;
	texture3.loadFromFile("photo/blocks.png");
	int y3 = 1;
	Sprite block3[300];

	Texture texture4;
	texture4.loadFromFile("photo/blocks.png");
	int y4 = 1;
	Sprite block4[300];

	for (int i = 0; i < 300; i++)
	{
		//	if (draw1)
		{
			block1[i].setTexture(texture1);
			block1[i].setTextureRect(IntRect(0, 0, 120, 100));
			block1[i].setPosition(Vector2f(25, 100 * y1));
			y1 -= 7;
		}

		block2[i].setTexture(texture2);
		block2[i].setTextureRect(IntRect(0, 0, 120, 100));
		block2[i].setPosition(Vector2f(170, 100 * y2));
		y2 -= 7;

		block3[i].setTexture(texture3);
		block3[i].setTextureRect(IntRect(0, 0, 120, 100));
		block3[i].setPosition(Vector2f(315, 100 * y3));
		y3 -= 7;

		block4[i].setTexture(texture4);
		block4[i].setTextureRect(IntRect(0, 0, 120, 100));
		block4[i].setPosition(Vector2f(460, 100 * y4));
		y4 -= 7;
	}

	//Drawing fruits**
	//FRUIT1 && FRUIT2  **

	Texture texture5;
	texture5.loadFromFile("photo/DIAMOND.png");
	int y5 = 1;
	Sprite fruit1[300];

	Texture texture6;
	texture6.loadFromFile("photo/DIAMOND.png");
	int y6 = 1;
	Sprite fruit2[300];

	for (int i = 0; i < 300; i++){
		fruit1[i].setTexture(texture5);
		fruit1[i].setTextureRect(IntRect(0, 0, 30, 30));
		srand(time(NULL));
		fruit1[i].setPosition(Vector2f((rand() % 241) + 10, (rand() % 301 * y5) + 300 * y5));
		y5 -= 2;

		fruit2[i].setTexture(texture6);
		fruit2[i].setTextureRect(IntRect(0, 0, 30, 30));
		fruit2[i].setPosition(Vector2f((rand() % 271) + 260, (rand() % 301 * y6) + 300 * y6));
		y6 -= 2;
	}
	// 10:250  && 300:600 for fruit1 
	//260:530 && 300:600 for fruit2
	//**

	//Drawing the snake***
	Texture texture8;
	texture8.loadFromFile("photo/snake.png");
	texture8.setRepeated(true);
	Sprite player;
	player.setTexture(texture8);
	player.setPosition(Vector2f(300.0f, 750.0f));
	player.setScale(Vector2f(0.25, 0.25));
	Vector2<float>snakeSpeed(0, -7.0);

	//Drawing the tail***
	Texture tail;
	tail.loadFromFile("photo/tail.png");
	tail.setRepeated(true);
	Sprite t;
	t.setTexture(tail);
	t.setPosition(Vector2f(300.0f, 827));
	t.setScale(Vector2f(0.1, 0.1));
	Vector2<float>tailSpeed(0, -7.0);


	// PAUSE *

	Text pausemaek;
	pausemaek.setFont(font);
	pausemaek.setString("II");
	pausemaek.setCharacterSize(50);
	pausemaek.setStyle(Text::Style::Bold);
	pausemaek.setOrigin(25.0f, 50.0f);
	pausemaek.setPosition(Vector2f(600, 60));
	Vector2<float>pausemaekSpeed(0, -7.0);

	// SCORE *

	Text text1;
	text1.setFont(font);
	text1.setString("score: ");
	text1.setCharacterSize(40);
	text1.setStyle(Text::Style::Bold);
	text1.setOrigin(25.0f, 50.0f);
	text1.setPosition(Vector2f(30, 60));
	Vector2<float>text1Speed(0, -7.0);

	//COUNTER**

	Text text2;
	text2.setFont(font);
	text2.setString(" counter : ");
	text2.setCharacterSize(40);
	text2.setStyle(Text::Style::Bold);
	text2.setOrigin(25.0f, 50.0f);
	text2.setPosition(Vector2f(20, 90));
	Vector2<float>text2Speed(0, -7.0);

	//COUNTER snake** 
	stringstream ss;

	Text textcounter;
	textcounter.setFont(font);

	textcounter.setCharacterSize(40);
	textcounter.setStyle(Text::Style::Bold);
	textcounter.setOrigin(25.0f, 50.0f);
	textcounter.setPosition(Vector2f(180, 90));
	Vector2<float>textcounterSpeed(0, -7.0);


	//COUNTER score** 
	stringstream sss;

	Text textcounterscore;
	textcounterscore.setFont(font);

	textcounterscore.setCharacterSize(40);
	textcounterscore.setStyle(Text::Style::Bold);
	textcounterscore.setOrigin(25.0f, 50.0f);
	textcounterscore.setPosition(Vector2f(150, 60));
	Vector2<float>textcounterscoreSpeed(0, -7.0);

	//Window Game OOPEN **

	while (windowgame.isOpen())
	{
		ss.str("");
		ss << countersnake;
		textcounter.setString(ss.str());

		sss.str("");
		sss << score;
		textcounterscore.setString(sss.str());
		if (movement)
		{
			view.move(0.0f, -7.0f);
			pausemaek.move(pausemaekSpeed.x, pausemaekSpeed.y);
			text1.move(pausemaekSpeed.x, pausemaekSpeed.y);
			text2.move(pausemaekSpeed.x, pausemaekSpeed.y);
			textcounter.move(0.0f, -7.0f);
			textcounterscore.move(0.0f, -7.0f);
			player.move(snakeSpeed.x, snakeSpeed.y);
			t.move(tailSpeed.x, tailSpeed.y);
		}
		//music game**

		//**

		//WINDOW PAUSE***

		if (select_x >= 1244 && select_x <= 1262 && select_y >= 145 && select_y <= 187)
		{
			pause_window(windowgame, levelwindow);

		}
		//Window Game Events***

		Event event;
		while (windowgame.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				windowgame.close();
				break;
			case Event::Resized:
				cout << "New window width" << event.size.width << endl;
				cout << "New window hight" << event.size.height << endl;
				break;

			case Event::MouseButtonPressed:
				select_x = Mouse::getPosition().x;
				select_y = Mouse::getPosition().y;
				cout << "x=" << select_x << endl;
				cout << "y=" << select_y << endl;

			case Event::TextEntered:
				if (event.text.unicode < 128)
					printf("%c", event.text.unicode);
				break;
			}
		}

		windowgame.setView(view);
		windowgame.clear();
		windowgame.draw(background);
		windowgame.draw(pausemaek);
		windowgame.draw(text1);
		windowgame.draw(text2);
		windowgame.draw(textcounter);
		windowgame.draw(textcounterscore);
		windowgame.draw(player);
		windowgame.draw(t);
		//***collision

		int i = 0;
		for (; i < 300; i++){

			movement = 1;


			if (b1[i] != 0)
			if (player.getGlobalBounds().intersects(block1[i].getGlobalBounds()))
			{
				countersnake = countersnake - cou1[i];
				//cout << countersnake << endl;
				result = cou1[i];
				score = score + result;
				cout << score << endl;
				while (1)
				{
					if (cou1[i] == 0)
					{
						check1 = i;
						break;
					}
					else{
						cou1[i] = cou1[i] - 1;
						text_counter1[i] = Transformation(cou1[i]);
						text_counter1[i].setFont(font);
						text_counter1[i].setColor(Color::Green);
						windowgame.draw(text_counter1[i]);
						movement = 0;
						//cout << cou1[i] << endl;
					}
				}
				break;
			}

			if (b4[i] != 0)
			if (player.getGlobalBounds().intersects(block4[i].getGlobalBounds()))
			{
				countersnake = countersnake - cou4[i];
				//cout << countersnake << endl;
				result = cou4[i];
				score = score + result;
				cout << score << endl;
				while (1)
				{
					if (cou4[i] == 0)
					{
						check4 = i;
						break;
					}
					else{
						cou4[i] = cou4[i] - 1;
						text_counter1[i] = Transformation(cou1[i]);
						text_counter1[i].setFont(font);
						text_counter1[i].setColor(Color::Green);
						windowgame.draw(text_counter1[i]);
						movement = 0;
						//		cout << cou4[i] << endl;
					}
				}
				break;
			}
			if (b2[i] != 0)
			if (player.getGlobalBounds().intersects(block2[i].getGlobalBounds()))
			{
				countersnake = countersnake - cou2[i];

				result = cou2[i];
				score = score + result;

				while (1)
				{
					if (cou2[i] == 0)
					{
						check2 = i;
						break;
					}
					else{
						cou2[i] = cou2[i] - 1;
						text_counter1[i] = Transformation(cou1[i]);
						text_counter1[i].setFont(font);
						text_counter1[i].setColor(Color::Green);
						windowgame.draw(text_counter1[i]);
						movement = 0;

					}
				}
				break;
			}


			if (b3[i] != 0)
			if (player.getGlobalBounds().intersects(block3[i].getGlobalBounds()))
			{
				countersnake = countersnake - cou3[i];

				result = cou3[i];
				score = score + result;
				cout << score << endl;
				while (1)
				{
					if (cou3[i] == 0)
					{
						check3 = i;
						break;
					}
					else{
						cou3[i] = cou3[i] - 1;
						text_counter1[i] = Transformation(cou1[i]);
						text_counter1[i].setFont(font);
						text_counter1[i].setColor(Color::Green);
						windowgame.draw(text_counter1[i]);
						movement = 0;
					}
				}
				break;
			}




			if (player.getGlobalBounds().intersects(fruit1[i].getGlobalBounds()))
			{
				checkf1 = i;
				countersnake = countersnake + cou5;
				break;
			}
			if (player.getGlobalBounds().intersects(fruit2[i].getGlobalBounds()))
			{
				checkf2 = i;
				countersnake = countersnake + cou6;
				break;
			}
		}




		//*
		for (int i = 0; i < 300; i++)
		{

			if (checkf1 != i)
			{
				windowgame.draw(fruit1[i]);
				text_frcounter1.setPosition(Vector2f(fruit1[i].getPosition().x + 10, fruit1[i].getPosition().y - 20));
				windowgame.draw(text_frcounter1);
			}

			if (checkf2 != i){
				windowgame.draw(fruit2[i]);
				text_frcounter2.setPosition(Vector2f(fruit2[i].getPosition().x + 10, fruit2[i].getPosition().y - 20));
				windowgame.draw(text_frcounter2);
			}
		}

		//**

		for (int i = 0; i < 300; i++){
			if (b1[i]>0)
			if (check1 == i){ check1 = -1; }
			else
			{
				windowgame.draw(block1[i]);
				text_counter1[i].setPosition(Vector2f(block1[i].getPosition().x + 10, block1[i].getPosition().y + 10));
				windowgame.draw(text_counter1[i]);

			}



			if (b2[i] > 0)
			if (check2 == i){ check2 = -1; }
			else
			{
				windowgame.draw(block2[i]);
				text_counter2[i].setPosition(Vector2f(block2[i].getPosition().x + 10, block2[i].getPosition().y + 10));
				windowgame.draw(text_counter2[i]);

			}
			if (b3[i] > 0)
			if (check3 == i){ check3 = -1; }
			else
			{
				windowgame.draw(block3[i]);
				text_counter3[i].setPosition(Vector2f(block3[i].getPosition().x + 10, block3[i].getPosition().y + 10));
				windowgame.draw(text_counter3[i]);

			}

			if (b4[i] > 0)
			if (check4 == i){ check4 = -1; }
			else
			{
				windowgame.draw(block4[i]);
				text_counter4[i].setPosition(Vector2f(block4[i].getPosition().x + 10, block4[i].getPosition().y + 10));
				windowgame.draw(text_counter4[i]);

			}

		}
		windowgame.display();



		//Snake.Move***

		if (Keyboard::isKeyPressed(Keyboard::Key::Left) && player.getPosition().x > 0)
		{
			player.move(-4.0f, 0.0f);
			t.move(-4.0f, 0.0f);
		}
		if (Keyboard::isKeyPressed(Keyboard::Key::Right) && player.getPosition().x < 550)
		{
			player.move(4.0f, 0.0f);
			t.move(4.0f, 0.0f);
		}


		if (countersnake < 0) {
			Results_window(windowgame, levelwindow , window);


		}

	}
}

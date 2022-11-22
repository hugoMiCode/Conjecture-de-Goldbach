#include <SFML/Graphics.hpp>
#include <iostream>

void fillSize(std::vector<unsigned int>& primes, const unsigned int size);
void drawGraph(sf::RenderWindow* window, std::vector<std::pair<int, int>>* coord);

int xmax{ 0 };
int ymax{ 0 };
sf::Font font;
std::vector<std::pair<std::string, sf::Text>> tabText;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Conjecture de Goldbach");

	tabText.push_back(std::make_pair("one frame : ", sf::Text("", font, 20)));
	tabText.push_back(std::make_pair("fonction fillSize : ", sf::Text("", font, 20)));
	tabText.push_back(std::make_pair("fonction drawGraph : ", sf::Text("", font, 20)));
	tabText.push_back(std::make_pair("find ymax : ", sf::Text("", font, 20)));
	tabText.push_back(std::make_pair("new coord : ", sf::Text("", font, 20)));

	for (int i{ 0 }; i < tabText.size(); i++) {
		tabText[i].second.setPosition(0, i * 15);
		tabText[i].second.setFillColor(sf::Color::Black);
	}

	font.loadFromFile("JAi_____.ttf");

	std::vector<std::pair<int, int>> coord;
	std::vector<unsigned int> primes;

	bool pause{ false };
	bool graph{ true };
	int number{ 4 };
	int conteur{ 0 };

    while (window.isOpen())
    {
		sf::Clock clockFrame;
        sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Space)
					pause = !pause;
			}
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.key.code == sf::Mouse::Left)
					graph = !graph;
			}
		}


		if (!pause) {
			unsigned int i{ 0 };
			sf::Clock clock;
			do {
				if (i >= primes.size())
					fillSize(primes, i + 1);

				for (unsigned int j{ 0 }; primes[j] <= number - primes[i]; j++) {
					if (j + 1 >= primes.size())
						fillSize(primes, j + 2);

					if (primes[i] + primes[j] == number)
						conteur++;
				}

				i++;

			} while (2 * primes[i] <= number);
			tabText[4].second.setString(tabText[4].first + std::to_string(clock.getElapsedTime().asMicroseconds()));

			coord.push_back(std::make_pair(number, conteur));

			conteur = 0;
			number += 2;
		}

        window.clear(sf::Color::White);

		sf::Clock clockMax;
		for (auto const pair : coord) {
			if (pair.first > xmax)
				xmax = pair.first;
			if (pair.second > ymax) {
				ymax = pair.second;
				std::cout << pair.first << " ; " << pair.second << std::endl;
			}
		}

		tabText[3].second.setString(tabText[3].first + std::to_string(clockMax.getElapsedTime().asMicroseconds()));


		if (graph)
			drawGraph(&window, &coord);

		for (auto pair : tabText) {
			window.draw(pair.second);
		}

        window.display();

		tabText[0].second.setString(tabText[0].first + std::to_string(clockFrame.getElapsedTime().asMicroseconds()));
    }

    return 0;
}

void fillSize(std::vector<unsigned int>& primes, const unsigned int size)
{
	sf::Clock clock;

	if (primes.empty())
		primes.push_back(2);

	unsigned int number{ primes.back() + 1 };

	while (primes.size() <= size) {
		bool prime{ true };
		for (unsigned int i{ 0 }; primes[i] <= sqrt(number); i++) {
			if (number % primes[i] == 0) {
				prime = false;
				break;
			}
		}

		if (prime)
			primes.push_back(number);

		number++;
	}

	tabText[1].second.setString(tabText[1].first + std::to_string(clock.getElapsedTime().asMicroseconds()));
}

void drawGraph(sf::RenderWindow* window, std::vector<std::pair<int, int>>* coord)
{	
	sf::Clock clock;

	std::vector<std::pair<double, double>> tabPt;

	for (auto const pair : *coord) {
		std::pair<double, double> p{ double(pair.first) / double(xmax), double(pair.second) / double(ymax) };
		p.first *= 1280;
		p.second *= 720;
		tabPt.push_back(p);
	}

	sf::CircleShape pt(1);
	pt.setOrigin(pt.getRadius() / 2.f, pt.getRadius() / 2.f);
	pt.setFillColor(sf::Color::Red);

	for (auto const pair : tabPt) {
		pt.setPosition(pair.first, -pair.second);
		pt.move(0, 720);

		window->draw(pt);
	}

	tabText[2].second.setString(tabText[2].first + std::to_string(clock.getElapsedTime().asMicroseconds()));
}

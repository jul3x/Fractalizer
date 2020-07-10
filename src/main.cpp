#include <complex>
#include <array>
#include <iostream>
#include <thread>

#include "SFML/Graphics.hpp"
#include "SFML/Audio/Music.hpp"

//resolution of the window
const int width = 600;
const int height = 600;

int value (int x, int y, const std::complex<float>& z)  {
    std::complex<float> point((float)x/width-1.3, (float)y/height-0.5);
    std::complex<float> new_z = z;
    int nb_iter = 0;
    while (abs(new_z) < 1.5 && nb_iter <= 20) {
        new_z = new_z * new_z + point;
        nb_iter++;
    }
    if (nb_iter < 20)
        return (255*std::pow(nb_iter, 2.0))/400;
    else
        return 0;
}

void range(sf::VertexArray* array, int s, int e, const std::complex<float>& z, float factor) {
    for (int x = s; x < e; x++)
    {
        for (int y = 0; y < height; y++) {
            float v = value(x, y, z);
            (*array)[x * height + y].position = sf::Vector2f(x, y);
            (*array)[x * height + y].color = sf::Color(v , 0,  std::abs(std::sin(factor / 4.0f)) * 1.0f * v);

        }
    }
}

double findMod(double a, double b)
{
    double mod;
    // Handling negative values
    if (a < 0)
        mod = -a;
    else
        mod =  a;
    if (b < 0)
        b = -b;

    // Finding mod by repeated subtraction

    while (mod >= b)
        mod = mod - b;

    // Sign of result typically depends
    // on sign of a.
    if (a < 0)
        return -mod;

    return mod;
}

int main() {
    sf::String title_string = "Mandelbrot Set Plotter";
    sf::RenderWindow window(sf::VideoMode(width, height), title_string);
    window.setFramerateLimit(30);
    auto pointmap = std::make_unique<sf::VertexArray>(sf::Points, width * height);
    sf::View view({width/2.0f, height/2.0f}, {width, height});
    window.setView(view);

    sf::Music music;

    music.openFromFile("../music.ogg");
    music.play();

    float r = -0.1;
    float i = -0.1;
    float factor = 1;
    const float bpm = 130.0f;
    float beats_distance = 60.0f / bpm;
    float velocity = 0.0f, acceleration = 5.0f;
    sf::Clock clock;
    sf::Time time_elapsed, fully_elapsed{};
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        std::complex<float> z(r, i);

        std::thread thread1(range, pointmap.get(), 0, width / 12, z, factor);
        std::thread thread2(range, pointmap.get(), width / 12, width / 6, z, factor);
        std::thread thread3(range, pointmap.get(), width / 6, width / 12 * 3, z, factor);
        std::thread thread4(range, pointmap.get(), width / 12 * 3, width / 4, z, factor);
        std::thread thread5(range, pointmap.get(), width / 4, width / 12 * 5, z, factor);
        std::thread thread6(range, pointmap.get(), width / 12 * 5, width / 2, z, factor);
        std::thread thread7(range, pointmap.get(), width / 2, width / 12 * 7, z, factor);
        std::thread thread8(range, pointmap.get(), width / 12 * 7, width / 12 * 8, z, factor);
        std::thread thread9(range, pointmap.get(), width / 12 * 8, width / 12 * 9, z, factor);
        std::thread thread10(range, pointmap.get(), width / 12 * 9, width / 12 * 10, z, factor);
        std::thread thread11(range, pointmap.get(), width / 12 * 10, width / 12 * 11, z, factor);
        std::thread thread12(range, pointmap.get(), width / 12 * 11, width, z, factor);

        thread1.join();
        thread2.join();
        thread3.join();
        thread4.join();
        thread5.join();
        thread6.join();
        thread7.join();
        thread8.join();
        thread9.join();
        thread10.join();
        thread11.join();
        thread12.join();

        if (std::abs(findMod(fully_elapsed.asSeconds() + 0.2f, beats_distance)) < 0.1f)
            velocity = 1.5f;

        //float velocity = 0.3 * std::pow(std::sin(fully_elapsed.asSeconds() * 0.5 * M_PI / bpm / 60.0f), 4.0) + 0.1;
        factor += velocity * time_elapsed.asSeconds();

        if (factor == 2*M_PI) factor = -2*M_PI;

        r = 1.3 * std::cos(factor);

//        auto view = window.getView();
//        view.setRotation(r * 10.0f);
//        window.setView(view);

        velocity -= acceleration * time_elapsed.asSeconds();
        if (velocity < 0.0f) velocity = 0.0f;

        window.clear();
        window.draw(*pointmap);
        window.display();
        time_elapsed = clock.getElapsedTime();
        fully_elapsed += time_elapsed;
        clock.restart();
    }

    return 0;
}

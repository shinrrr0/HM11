#include <iostream>
#include <vector>
#include <string>

// Абстрактный класс для плодов
class Harvest {
public:
    Harvest(const std::string& name, int weight, const std::string& color)
        : name(name), weight(weight), color(color) {}

    virtual ~Harvest() = default;

    virtual std::string get_info() const = 0; // Чисто виртуальная функция

protected:
    std::string name;
    int weight;
    std::string color;
};

// Абстрактный класс для растений
class Plant {
public:
    Plant(const std::string& size, const std::string& color, int max_fruits)
        : size(size), color(color), max_fruits(max_fruits) {}

    virtual ~Plant() {
        // Освобождаем память от плодов при уничтожении объекта растения
        for (const auto& fruit : current_fruits) {
            delete fruit;
        }
    }

    virtual Harvest* create_fruit(const std::string& name, int weight, const std::string& color) = 0; // Чисто виртуальная функция

    void harvest_fruits() {
        if (current_fruits.empty()) {
            std::cout << "На растении нет плодов для сбора." << std::endl;
        }
        else {
            for (const auto& fruit : current_fruits) {
                std::cout << fruit->get_info() << std::endl;
            }
            current_fruits.clear();
        }
    }

    void add_to_current_fruits(Harvest* fruit) {
        current_fruits.push_back(fruit);
    }

    const std::vector<Harvest*>& get_current_fruits() {
        return current_fruits;
    }

protected:
    std::string size;
    std::string color;
    int max_fruits;
    std::vector<Harvest*> current_fruits;
};

// Конкретный класс для плода - яблоко
class Apple : public Harvest {
public:
    Apple(const std::string& name, int weight, const std::string& color)
        : Harvest(name, weight, color) {}

    std::string get_info() const override {
        return name + ": " + std::to_string(weight) + " г, цвет: " + color;
    }
};

// Конкретный класс для растения - яблоня
class AppleTree : public Plant {
public:
    AppleTree() : Plant("средний", "зелёный", 10) {}

    Harvest* create_fruit(const std::string& name, int weight, const std::string& color) override {
        return new Apple(name, weight, color);
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    // Создаем яблоню
    AppleTree apple_tree;

    // Создаем плоды на яблоне
    Harvest* apple1 = apple_tree.create_fruit("Красное яблоко", 150, "красное");
    Harvest* apple2 = apple_tree.create_fruit("Зеленое яблоко", 120, "зеленое");

    // Добавляем плоды на дерево
    apple_tree.add_to_current_fruits(apple1);
    apple_tree.add_to_current_fruits(apple2);

    // Собираем плоды
    apple_tree.harvest_fruits();

    return 0;
}
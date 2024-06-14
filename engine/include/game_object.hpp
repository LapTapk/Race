#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <vector>
#include <memory>
#include <typeinfo>

class Transform;
class Component;

/**
 * Класс, отвечающий за основную единицу игры. 
 * Обладает компонентами, определяющими его поведение
*/
class GameObject {
public:
    GameObject* parent;///< Родительский объект
    std::vector<std::unique_ptr<Component>> components;///< Компоненты объекта
    std::vector<std::unique_ptr<GameObject>> children;///< Дети объекта
    Transform* transform;///< Основной компонент Transform
    void update();///< Функция подсчета кадра, активирует подсчет кадров каждого компоненты components
    /**
     * Функция удаления компонента 
     * 
     * @param cmp Указатель на компонент, который следуюет удалить
    */
    void remove_cmp(Component* cmp); 
    /**
     * Инициализатор GameObject, который является сценой.
     * Родительский объект равен nullptr
    */
    GameObject();
    /**
     * Инициализатор GameObject
     * 
     * @param parent Родительский объект
    */
    GameObject(GameObject* parent);
    /**
     * Деструктор GameObject. Запускает деструкторы 
     * компонентов и детей 
    */
    ~GameObject();
};

/**
 * Базовый класс, отвечающий за определение поведения GameObject
*/
class Component {
public:
    GameObject* go;///< Родительский объект
    virtual void update() {}; ///< Функция подсчета кадра
    /**
     * Конструктор Component
     * 
     * @param go Родительский объект
    */
    Component(GameObject* go);
};
#endif
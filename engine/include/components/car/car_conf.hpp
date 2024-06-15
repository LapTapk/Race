#ifndef CAR_CONF_HPP
#define CAR_CONF_HPP

/** 
 * Структура конфигурации машины
 */
struct CarConf {
    float max_speed, acceleration,
        friction, rotation_delta, decelerate_coef;
};

#endif
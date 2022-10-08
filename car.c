#include "car.h"

Car *new_car(int pos_x, int pos_y, int speed) {
    Car *car = (Car*)malloc(sizeof(Car));
    Moveable *moveable = (Moveable*)malloc(sizeof(Moveable));

    moveable->pos_x = pos_x;
    moveable->pos_y = pos_y;
    moveable->speed = speed;

    car->moveable = moveable;
    car->spec = speed > 0 ? CAR_SPEC_RIGHT : CAR_SPEC_LEFT;
 
    return car;
}

void draw_car(Car* car) {
    draw(car->spec, car->moveable);
}

void move_car(Car *car, int tick) {

    Moveable *moveable = car->moveable;

    if(tick % (int)(FPS/fabs(moveable->speed)) == 0 ) {
        if(moveable->speed > 0) {
        moveable->pos_x = (moveable->pos_x + 1) % WIDTH; 
        } else {
            moveable->pos_x = moveable->pos_x == 0 ? WIDTH - 1: moveable->pos_x - 1;
        }
    }
}

Car** generate_cars() {
    Car **cars = (Car**)malloc(MAX_AMOUNT_CARS * sizeof(Car*));

    int index = 0;
    for(int i = 0; i < NUMBER_OF_CAR_ROWS; i++) {
        int number_of_cars_in_row = (rand() % MAX_NUMBER_OF_CAR_IN_ROW) + 1;

        int space_step = (MAX_CAR_SPEED - MIN_CAR_SPEED) / MAX_NUMBER_OF_CAR_IN_ROW;
        int speed_of_cars_in_row = MAX_CAR_SPEED - (space_step * number_of_cars_in_row) + (rand() % 3);
        if(i % 2 == 0) {
            speed_of_cars_in_row *= -1;
        }
        int car_spacing = WIDTH/number_of_cars_in_row;
        int delta_initial_pos = rand() % WIDTH; 
        for(int j = 0; j < number_of_cars_in_row; j++) {

            Car *car = new_car(j * car_spacing + delta_initial_pos, HEIGHT - ((i + 2) * 2) ,  speed_of_cars_in_row); 
            cars[index] = car;
            index++;
        }
    }
    return cars;
}

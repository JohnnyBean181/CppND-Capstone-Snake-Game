#include "food.h"

Food::Food (int x, int y){

    SDL_Point point = {x, y};
    position = std::make_unique<SDL_Point>(point);

    // set up decay time, from 6-11 sec randomly.
    srand( SDL_GetTicks() );
    time_to_decay = 6 + rand() % 6;

    // set up poisoness
    if (rand() % 5 == 0) {
        type = FoodType::poisonous;
    } else {
        type = FoodType::normal;
    }
}

SDL_Point* Food::GetPosition() {
    return position.get();
}
// return timestamp when the food is generated. (in ms)
Uint32 Food::GetTimeStamp() {
    return start_timestamp;
}

bool Food::IsPoisonous() {
    if (type == FoodType::poisonous) {
        return true;
    }

    return false;
}
// return how many time should the food decay. (in s)
int Food::GetDecayTime() {
    return time_to_decay;
}
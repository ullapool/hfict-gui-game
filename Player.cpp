#include "Player.h"
#include "Constants.h"

Player::Player(int x, int y) : GameObject (x, y, Constants::playerImgFile, Constants::playerWidth) {}

void Player::move() {}

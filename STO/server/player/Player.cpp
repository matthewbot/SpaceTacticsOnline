#include "Player.h"
#include "PlayerController.h"

using namespace sto;
using namespace std;

Player::Player(int id, const string &name, PlayerController *controller)
: id(id), name(name), controller(controller) { }

Player::~Player() { }


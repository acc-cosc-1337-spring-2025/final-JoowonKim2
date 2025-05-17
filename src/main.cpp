#include <iostream>
#include <ctime>
#include "die.h"
#include "roll.h"
#include "shooter.h"
#include "come_out_phase.h"
#include "point_phase.h"

using std::cout;
using std::endl;

int main() 
{
	Die die1;
    Die die2;
	Shooter shooter;
	Roll* roll {};
    int rolled_value {};
	ComeOutPhase come_out_phase;

	do {
		roll = shooter.throw_dice(die1, die2);
		rolled_value = roll -> roll_value();
		if (come_out_phase.get_outcome(roll) != RollOutcome::point)
			cout << "Rolled " << rolled_value << " roll again\n";
	} while (come_out_phase.get_outcome(roll) != RollOutcome::point);

	cout << "Rolled " << rolled_value << " start of point phase\n";
	cout << "Roll until " << rolled_value <<" or 7 is rolled\n";

	int point = rolled_value;
	PointPhase point_phase(point);

	do {
		roll = shooter.throw_dice(die1, die2);
		rolled_value = roll -> roll_value();
		if (point_phase.get_outcome(roll) == RollOutcome::nopoint)
			cout << "Rolled " << rolled_value << " roll again \n";
	} while (point_phase.get_outcome(roll) == RollOutcome::nopoint);

	cout << "Rolled " << rolled_value << " end of point phase\n";
	cout << "Game Over\n";
	shooter.display_rolled_values();

	return 0;
}
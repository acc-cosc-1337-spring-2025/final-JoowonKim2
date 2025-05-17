#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "die.h"
#include "roll.h"
#include "shooter.h"
#include "phase.h"
#include "point_phase.h"
#include "come_out_phase.h"

TEST_CASE("Verify Test Configuration", "verification") {
	REQUIRE(true == true);
}

TEST_CASE("Test Die") 
{
    Die die;

    for (int i = 0; i < 10; ++i) {
        int roll_result = die.roll();
        REQUIRE(roll_result >= 1);
        REQUIRE(roll_result <= 6);
    }
}

TEST_CASE("Test Roll"){
    Die die1, die2;
    Roll rolls(die1, die2);
    
    for(int i; i <= 10; i++){
        rolls.roll_dice();
        REQUIRE(rolls.roll_value() >= 2);
        REQUIRE(rolls.roll_value() <= 12);
    }
}

TEST_CASE("Test Shooter"){
    Die die1, die2;
    Shooter shooter;

    for (int i = 0; i < 10; ++i) {
        Roll* roll = shooter.throw_dice(die1, die2);
        int result = roll->roll_value();
        REQUIRE(result >= 2);
        REQUIRE(result <= 12);
    }
}

TEST_CASE("Test ComeOutPhase") {

	Die d1;
	Die d2;
	ComeOutPhase phase;

	std::vector<Roll*> rolls;
	bool get_natural = false, get_craps = false, get_point = false;

	do {
		Roll roll {d1, d2};
		roll.roll_dice();
		rolls.push_back(&roll);
		
		if (roll.roll_value() == 7 || roll.roll_value() == 11) {
			REQUIRE(phase.get_outcome(&roll) == RollOutcome::natural);
			get_natural = true;
		}
		else if (roll.roll_value() == 2 || roll.roll_value() == 3 || roll.roll_value() == 12) {
			REQUIRE(phase.get_outcome(&roll) == RollOutcome::craps);
			get_craps = true;
		}
		else {
			REQUIRE(phase.get_outcome(&roll) == RollOutcome::point);
			get_point = true;
		}

		if (rolls.size() >= 24)
			break;
		
	} while (!get_natural || !get_craps || !get_point);
}

TEST_CASE("Test PointPhase") {

	Die d1;
	Die d2;
	int point = 5;
	PointPhase phase(point);

	std::vector<Roll*> rolls;
	bool get_point = false, get_sevenout = false, get_nopoint = false;

	do {
		Roll roll {d1, d2};
		roll.roll_dice();
		rolls.push_back(&roll);

		if (roll.roll_value() == 7) {
			REQUIRE(phase.get_outcome(&roll) == RollOutcome::seven_out);
			get_sevenout = true;
		}
		else if (roll.roll_value() == point) {
			REQUIRE(phase.get_outcome(&roll) == RollOutcome::point);
			get_point = true;
		}
		else {
			REQUIRE(phase.get_outcome(&roll) == RollOutcome::nopoint);
			get_nopoint = true;
		}

		if (rolls.size() >= 24)
			break;

	} while (!get_point || !get_sevenout || !get_nopoint);
}
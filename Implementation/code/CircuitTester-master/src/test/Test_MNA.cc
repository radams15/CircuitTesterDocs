/** @file nodal_analysis.cpp
 * This tests the modified nodal analysis code
 */
//
// Created by rhys on 09/05/2021.
//

#include <gtest/gtest.h>

#include "../main/Analysis/MNAComponent.h"
#include "../main/Analysis/MNACircuit.h"
#include "../main/Analysis/MNASolution.h"

/**
 * @brief One Resistor Current.
 * Tests to see if the current of one 4.0 &Omega; resistor
 * connected to a 10.0V battery is 2.5A.
 */
TEST(NodalAnalysis, OneResistorCurrent){
    auto bat = new MNAComponent(0, 1, BATTERY, 10);
    auto res = new MNAComponent(1, 0, RESISTOR, 4);

    auto cir = new MNACircuit({bat, res});

    std::map<int, double> vmap = {
            {0, 0.0},
            {1, 10.0},
    };

    auto dessol = new MNASolution(vmap, {bat});

    auto sol = cir->solve();

    ASSERT_EQ(sol->equals(*dessol), true);

    ASSERT_EQ(sol->getCurrent(*res), 2.5);
}


/**
 * @brief Two Resistors In Parallel.
 * Tests to see if the currents of two resistors
 * of resistances 10.0 &Omega; and 20.0 &Omega; on a
 * 10V battery are 1.0A and 0.5A respectively to test
 * current splitting.
 */
TEST(NodalAnalysis, TwoResistorsInParallel){
    auto bat = new MNAComponent(0, 1, BATTERY, 10);
    auto res1 = new MNAComponent(1, 0, RESISTOR, 10);
    auto res2 = new MNAComponent(1, 0, RESISTOR, 20);

    auto cir = new MNACircuit({bat, res1, res2});

    std::map<int, double> vmap = {
            {0, 0.0},
            {1, 10.0},
            {2, 10.0},
    };

    auto dessol = new MNASolution(vmap, {bat->withCurrentSolution(1.5)});

    auto sol = cir->solve();

    ASSERT_EQ(sol->equals(*dessol), true);

    ASSERT_EQ(sol->getCurrent(*res1), 1.0);
    ASSERT_EQ(sol->getCurrent(*res2), 0.5);
}

/**
 * @brief Parallel And Series Resistors.
 *
 * Two resistors in series (5 &Omega; and 10 &Omega;) connected to
 * one 7 &Omega; resistor, connected to a 9V battery.
 *
 * Currents should be 0.58A, 0.29A and 0.87A respectively.
 */
TEST(NodalAnalysis, ParalellAndSeriesResistors){
    auto bat = new MNAComponent(0, 1, BATTERY, 9);
    auto res1 = new MNAComponent(1, 2, RESISTOR, 5);
    auto res2 = new MNAComponent(1, 2, RESISTOR, 10);
    auto res3 = new MNAComponent(2, 0, RESISTOR, 7);

    auto cir = new MNACircuit({bat, res1, res2, res3});

    std::map<int, double> vmap = {
            {0, 0.0},
            {1, 9.0},
            {2, 6.09677},
    };

    auto dessol = new MNASolution(vmap, {bat->withCurrentSolution(0.870968)});

    auto sol = cir->solve();

    ASSERT_EQ(sol->equals(*dessol), true);

    ASSERT_DOUBLE_EQ(round(sol->getCurrent(*res1) * 100) / 100, 0.58);
    ASSERT_DOUBLE_EQ(round(sol->getCurrent(*res2) * 100) / 100, 0.29);
    ASSERT_DOUBLE_EQ(round(sol->getCurrent(*res3) * 100) / 100, 0.87);
}


/**
 * @brief Two Batteries In Series.
 * Tests to see if the voltage of two 4.0V
 * batteries are added together to get a total
 * of 8.0V.
 */
TEST(NodalAnalysis, TwoBatteriesInSeries){
    auto bat1 = new MNAComponent(0, 1, BATTERY, 3);
    auto bat2 = new MNAComponent(1, 2, BATTERY, 4);
    auto res = new MNAComponent(2, 0, RESISTOR, 2);

    auto cir = new MNACircuit({bat1, bat2, res});

    std::map<int, double> vmap = {
            {0, 0.0},
            {1, 3.0},
            {2, 7.0},
    };

    auto dessol = new MNASolution(vmap, {bat1->withCurrentSolution(3.5), bat2->withCurrentSolution(3.5)});

    auto sol = cir->solve();

    ASSERT_EQ(sol->equals(*dessol), true);
}

/**
 * @brief Two Batteries In Parallel.
 * Tests to see if the voltage of two 4.0V
 * batteries is 4.0V, and have a current of
 * 0.2A.
 * Also tests if the values are identical to
 * if there is only 1 4.0V battery.
 */
TEST(NodalAnalysis, TwoBatteriesInParallel){
    auto bat1 = new MNAComponent(0, 1, BATTERY, 4);
    auto bat2 = new MNAComponent(0, 1, BATTERY, 4);
    auto res = new MNAComponent(1, 0, RESISTOR, 10);

    auto cir = new MNACircuit({bat1, bat2, res});

    std::map<int, double> vmap = {
            {0, 0.0},
            {1, 4.0},
    };

    auto dessol = new MNASolution(vmap, {bat1->withCurrentSolution(0.4), bat2->withCurrentSolution(0.0)});

    auto sol = cir->solve();

    ASSERT_EQ(sol->equals(*dessol), true);
}
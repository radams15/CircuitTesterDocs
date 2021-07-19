/**
 * @author Rhys Adams
 * @date 18/04/2021
 */

#ifndef CircuitTester_EQUATION_H
#define CircuitTester_EQUATION_H

#include <string>
#include <vector>

#include <Eigen/Core>

#include "MNAComponent.h"
#include "Unknown.h"
#include "Term.h"

/** @brief Class that holds an equation.
 *
 * An equation is 2x + 3b = 5 where 2x and 3b
 * are the terms, and 5 us the value.
 */
class Equation {
private:

public:
    /** @brief The value the terms equal
     * In 1a + 2b = 3 this is 3.
     */
    double value;

    /** @brief The value the terms equal
     * In 1a + 2b = 3 this is an array {1a, 2b}.
     */
    std::vector<Term*> terms;

    /** @brief Initialiser
     *
     * @param value The value of the equation
     * @param terms The Term objects that equal the value when added.
     */
    Equation(double value, std::vector<Term*> terms);

    /** @brief Stamps the parts of this component onto the passed matrix to form the overall equation.
     *
     * @param row The row to apply the value of the equation onto.
     * @param A Stores connections, voltage sources, and independent current sources.
     * @param z Stores independent current and voltage sources.
     * @param getIndexFunc A function that returns the index of the Unknown on the circuit that is passed into it.
     */
    void apply(int row, Eigen::MatrixXd* A, Eigen::MatrixXd* z, std::function<int(Unknown*)> getIndexFunc);

    /** @brief String representation of the Equation (for debugging).
     *
     * @return The string representation.
     */
    std::string str();
};


#endif //CircuitTester_EQUATION_H

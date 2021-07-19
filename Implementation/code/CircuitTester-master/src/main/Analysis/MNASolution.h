/**
 * @author Rhys Adams
 * @date 18/04/2021
 */

#ifndef CircuitTester_MNASOLUTION_H
#define CircuitTester_MNASOLUTION_H

#include <map>
#include <vector>
#include <string>

#include "MNAComponent.h"

/** @brief Stores the solution of a circuit.
 *
 * This class stores the voltage map, and every element that has
 * a known current so that voltages can be calculated through V=IR.
 *
 */
class MNASolution {
private:
    /** @brief Check whether double a is equal to double b.
     *
     * This compares two double values by subtracting, getting the
     * absolute value, then comparing the difference to an epsilon,
     * which here is 1x10^-6.
     *
     * @param a The first double
     * @param b The second double
     * @return Whether they are equal or not
     */
    static bool numApproxEquals(double a, double b);

    /** @brief Whether this solution has all the same elements
     * as the other solution.
     *
     * @param mnaSolution The other MNASolution to compare to this.
     * @return Whether the two solutions are equal.
     */
    bool hasAllElements(MNASolution mnaSolution);

    /** @brief Determines if element is in this solution.
     *
     * @param element The element to check exists.
     * @return Whether the element is inside the elements
     * list.
     */
    bool containsElement(MNAComponent* element);

public:
    /** @brief A map of node:voltage.
     *
     */
    std::map<int, double> voltageMap;

    /** @brief A list of elements in the solution which
     * have a known current.
     */
    std::vector<MNAComponent*> elements;

    /** @brief Initialiser
     *
     * @param voltageMap A map of node:voltage
     * @param elements A list of elements in the solution which
     * have a known current.
     */
    MNASolution(std::map<int, double> voltageMap, std::vector<MNAComponent*> elements);

    /** @brief Whether this has every element and every element is
     * approximately equal to the other in the opposing MNASolution.
     *
     * @param mnaSolution
     * @return
     */
    bool equals(MNASolution mnaSolution);

    /** @brief Get the voltage at a specific node.
     *
     * @param nodeIndex The node to check at.
     * @return The voltage at that node.
     */
    double getNodeVoltage(int nodeIndex);

    /** @brief Get the voltage of a specified element.
     *
     * @param element The MNAComponent to check at.
     * @return The voltage at that element.
     */
    double getVoltage(MNAComponent element);

    /** @brief Gets the current at a resistor through I=V/R
     *
     * @param resistor The resistor to get the current of
     * @return The current at that resistor.
     */
    double getCurrent(MNAComponent resistor);
};


#endif //CircuitTester_MNASOLUTION_H

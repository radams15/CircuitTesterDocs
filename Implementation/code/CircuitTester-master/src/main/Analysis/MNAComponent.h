/** @brief Element class for the modified nodal analysis
 * @author Rhys Adams
 * @date 18/04/2021
 */

#ifndef CircuitTester_MNAELEMENT_H
#define CircuitTester_MNAELEMENT_H

#include <cmath>

enum ElementType{
    BATTERY,
    RESISTOR
};

/**@brief Main class that holds circuit elements for
 * modified nodal analysis (MNA).
 */
class MNAComponent {
private:

public:
    /** @brief Start node.
     *
     * The node index of the beginning of this element.
     */
    int n0;

    /** @brief End node.
     *
     * The node index of the end of this element.
     */
    int n1;

    /** @brief Component value.
     *
     * This stores the resistance for resistors, the voltage for batteries
     * and the current for current sources.
     */
    double value;

    /** @brief Current
     *
     * The current for this element.
     */
    double currentSolution;

    /** @brief Element Type
     *
     * This is set by derivative classes, can be BATTERY, RESISTOR or CURRENT_SRC
     */
    ElementType type;

    /** @brief Initialiser
     *
     * @param n0 The start node
     * @param n1 The end node
     * @param type The element type
     * @param value The value of this component
     * @param currentSolution The current solution if needed, otherwise it is just NAN
     */
    MNAComponent(int n0, int n1, ElementType type, double value, double currentSolution=NAN);

    /** @brief With specified current solution.
     *
     * New element with identical values but with a different current solution.
     *
     * @param newCurrentSolution The current solution for the new element to have.
     * @return
     */
    MNAComponent* withCurrentSolution(double newCurrentSolution);

    /** @brief Node in this element.
     *
     * Returns true if either n0 or n1 equals n.
     *
     * @param n The node to check.
     * @return whether n is contained by this element.
     */
    bool contains(int n);

    /** @brief Get opposite node to passed
     *
     * Returns n1 if passed n is n0 otherwise returns n0.
     *
     * @param n The node to find the opposite of
     * @return The opposite node to n
     */
    int opposite(int n);

    /** @brief Equality to another node.
     *
     * @param other The node to compare against.
     * @return Whether other has the same contents as this element.
     */
    bool equals(MNAComponent other);
};


#endif //CircuitTester_MNAELEMENT_H

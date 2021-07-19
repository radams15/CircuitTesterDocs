/** @brief
 * @author Rhys Adams
 * @date 18/04/2021
 */

#ifndef CircuitTester_MNACIRCUIT_H
#define CircuitTester_MNACIRCUIT_H

#include <vector>
#include <map>
#include <string>

#include "MNAComponent.h"
#include "Equation.h"
#include "MNASolution.h"

/** @brief Main class that holds a circuit for
 * modified nodal analysis (MNA).
 *
 */
class MNACircuit {
private:
    /** @brief Holds all the MNAElements that are batteries */
    std::vector<MNAComponent*> batteries;

    /** @brief Holds all the MNAElements that are resistors */
    std::vector<MNAComponent*> resistors;

    /** @brief Holds all the MNAElements combined */
    std::vector<MNAComponent*> elements;

    /** @brief The total number of nodes */
    int nodeCount;

    /** @brief All the nodes in the circuit*/
    std::vector<int> nodes;

    /** @brief Pops and returns the first element of the vector vec.
     *
     * This was written as the STL only has a pop_back method, not
     * a pop_front method.
     *
     * @tparam T The type that is in the vector.
     * @param vec A vector to remove the first element of
     * @return The first element that was removed.
     */
    template<typename T>
    T vecPopFront(std::vector<T>& vec);

    /** @brief Gets the number of unknown currents.
     *
     * Current sources are not calculated as they are known currents.
     *
     * @return The number of unknown currents.
     */
    int getNumUnknownCurrents();

    /** @brief Used to find out the number of both current and voltage variables.
     *
     * @return The total number of variables in the circuit.
     */
    int getNumVars();

    /** @brief Selects the components that have the reference voltage.
     *
     * This is the voltage that other components are comparedto.
     *
     * @return A list of nodes that are references.
     */
    std::vector<int>* getRefNodes();

    /** @brief Returns a list of equations that must be solved
     * to solve the overall circuit.
     *
     * @return A list of solvable Equation objects.
     */
    std::vector<Equation*>* getEquations();

    /** @brief Returns all unknown currents in thecircuit
     *
     * @return A list of all the UnknownCurrent objects.
     */
    std::vector<UnknownCurrent*>* getUnknownCurrents();

    /** @brief Returns the index of the element in the array.
     *
     * If it does not exist, returns -1.
     *
     * @tparam T The type of the vector, and of the element.
     * @param array The vector of T's.
     * @param element The element to search for.
     * @return The element index in the vector, or -1 if the element is not found.
     */
    template <typename T>
    int getElementIndex(std::vector<T*>* array, T* element);

public:
    /** @brief Initialises MNACircuit object.
     *
     * This initialises the MNACircuit, as well as categorising
     * the elements into the batteries, resistors and currentSources
     * vectors. Also generates nodeSet, nodeCount and nodes variables.
     *
     * @param elements The list of all circuit elements.
    */
    explicit MNACircuit(std::vector<MNAComponent *> elements);

    /** @brief Solves the circuit using linear algebra and matrices.
     *
     * @return An MNASolution class for this circuit.
     */
    MNASolution* solve();

    /** Finds the nodes that are connected to the passed node.
     *
     * @param node The node to search around.
     * @return
     */
    std::vector<int>* getConnectedNodes(int node);

    /** @brief Gets the terms that enter and leave a node.
     *
     * Incoming is negative, outgoing is positive
     *
     * @param node The node to search around.
     * @param side The side we are referring to - 1 for incoming, 0 for outgoing.
     * @return
     */
    std::vector<Term*>* getCurrents(int node, int side);
};

#endif //CircuitTester_MNACIRCUIT_H

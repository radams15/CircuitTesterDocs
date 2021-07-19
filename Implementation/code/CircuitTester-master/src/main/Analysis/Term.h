/** @brief Class that holds a term.
 *
 * Terms are in the form 2x where 2 is the
 * coefficient and x is the variable.
 *
 * @author Rhys Adams
 * @date 13/05/2021
 */

#ifndef CIRCUITTESTER_TERM_H
#define CIRCUITTESTER_TERM_H


#include "Unknown.h"

class Term {
private:

public:
    /** @brief The coefficient of the term.
     *
     * This is the 2 in 2x.
     *
     */
    double coefficient;

    /** @brief The variable in the term.
     *
     * This is the x in 2x.
     *
     */
    Unknown* variable;

    /** @brief Initialiser.
     *
     * @param coefficient
     * @param variable
     */
    Term(double coefficient, Unknown* variable);

    /** @brief String representation (for debugging)
     *
     * @return The string representation.
     */
    std::string str();
};


#endif //CIRCUITTESTER_TERM_H

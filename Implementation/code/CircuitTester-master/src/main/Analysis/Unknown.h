/**
 * @author Rhys Adams
 * @date 9/05/2021
 */


#ifndef CIRCUITTESTER_UNKNOWN_H
#define CIRCUITTESTER_UNKNOWN_H

#include <string>
#include "MNAComponent.h"

/** @brief Base class for unknown values
 *
 * This is a base class for UnknownCurrent
 * and UnknownVoltage, as they need to be reduced to
 * one base class for storage in a list.
 *
 */
class Unknown {
public:
    /** @brief The type of unknown - current or voltage.
     *
     */
    enum Type{
        CURRENT,
        VOLTAGE
    };

    /** @brief The type of the derivative class.
     *
     */
    Type type;

    /** @brief Whether this Unknown equals another.
     *
     * Compares the attributes and types to find equality.
     *
     * @param other The Unknown to compare against this.
     * @return Whether this and other have the same attributes.
     */
    virtual bool equals(Unknown* other) = 0;

    /** @brief Get string representation.
     *
     * @return The string representation of this Unknown.
     */
    virtual std::string str() = 0;

protected:

    /** @brief initialiser
     *
     * This is protected as it should only ever be called
     * by a derivative class, as a pure Unknown should never exist.
     *
     * @param t the Type of the new Unknown.
     */
    Unknown(Type t);
};


/** @brief Stores an MNAComponent for which the current is unknown.
 *
 */
class UnknownCurrent : public Unknown {
private:

public:
    /** @brief The element for which the current is unknown.
     *
     */
    MNAComponent* element;

    /** @brief Initialiser
     *
     * Initialises the UnknownCurrent by initialising an Unknown
     * of type CURRENT and setting this.element to element.
     *
     * @param element The element for which current is unknown.
     */
    explicit UnknownCurrent(MNAComponent* element);

    std::string str() override;
    bool equals(Unknown* other) override;
};

/** @brief Stores a node for which the voltage is unknown.
 *
 */
class UnknownVoltage : public Unknown {
private:

public:
    /** @brief The node for which voltage is unknown.
     *
     */
    int node;

    /** @brief Initialiser
     *
     * Initialises the UnknownVoltage by initialising an Unknown
     * of type VOLTAGE and setting this.node to node.
     *
     * @param node The npde for which voltage is unknown.
     */
    explicit UnknownVoltage(int node);

    std::string str() override;
    bool equals(Unknown* other) override;
};


#endif //CIRCUITTESTER_UNKNOWN_H

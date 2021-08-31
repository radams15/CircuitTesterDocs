import numpy as np

from MNAElement import MNAElement, ElementType
from MNASolution import MNASolution
from Resistor import Resistor
from Unknowns import UnknownCurrent, UnknownVoltage
from Equation import Term, Equation

def get_index_by_equals(array, element) -> int:
    for i in range(len(array)):
        if (type(array[i]) == type(element)) and (array[i] == element):
            return i

    return -1

class MNACircuit:
    def __init__(self, elements: list):
        self.batteries: list[MNAElement] = []
        self.resistors: list[MNAElement] = []
        self.current_sources: list[MNAElement] = []

        for e in elements:
            if e.type == ElementType.BATTERY:
                self.batteries.append(e)
            elif e.type == ElementType.RESISTOR:
                self.resistors.append(e)
            elif e.type == ElementType.CURRENT_SOURCE:
                self.current_sources.append(e)

        self.elements = self.batteries + self.resistors + self.current_sources

        self.nodes = []

        for e in self.elements:
            self.nodes.append(e.n0)
            self.nodes.append(e.n1)

        self.nodes = list(set(self.nodes))

        self.node_count = len(self.nodes)


    def __str__(self):
        return f"resistors: {map(str, self.resistors)}\nbatteries: {map(str, self.batteries)}\ncurrent sources: {map(str, self.current_sources)}"

    def get_num_vars(self):
        return self.node_count + len(self.batteries)

    def get_current_source_total(self, node_index):
        total = 0.0

        for c in self.current_sources:
            if c.n1 == node_index:
                total -= c.value
            if c.n0 == node_index:
                total += c.value

        return total

    def get_current_terms(self, node: int, side: int, sign: int) -> list:
        node_terms: list = []

        for b in self.batteries:
            b_side = b.n0 if side == 0 else b.n1

            if b_side == node:
                node_terms.append(Term(sign, UnknownCurrent(b)))

        for r in self.resistors:
            r_side = r.n0 if side == 0 else r.n1

            if r_side == node and r.value != 0:
                node_terms.append(Term(-sign/r.value, UnknownVoltage(r.n1)))
                node_terms.append(Term(sign/r.value, UnknownVoltage(r.n0)))

        return node_terms

    def get_ref_node_ids(self) -> list:
        to_visit: list[int] = self.nodes.copy()

        ref_node_ids: list[int] = []

        while len(to_visit) > 0:
            ref_node_id = to_visit[0]
            ref_node_ids.append(ref_node_id)
            connected = self.get_connected_node_ids(ref_node_id)

            for c in connected:
                to_visit.remove(c)

        return ref_node_ids


    def get_connected_node_ids(self, node: int):
        visited = []
        to_visit = [node]

        while len(to_visit) > 0:
            node_to_visit = to_visit.pop(0)

            visited.append(node_to_visit)

            for e in self.elements:
                if e.contains_node_id(node_to_visit):
                    opposite = e.get_opposite_node(node_to_visit)
                    if opposite not in visited:
                        to_visit.append(opposite)

        return list(set(visited))

    def get_equations(self) -> list:
        equations = []

        ref_node_ids = self.get_ref_node_ids()

        print(f"Reference nodes: {ref_node_ids}")

        for r in ref_node_ids: # ref nodes together have a voltage of 0
            equations.append(Equation(0, [
                Term(1, UnknownVoltage(r))
            ]))


        nodes = self.nodes

        for n in nodes:

            if n not in ref_node_ids:
                incoming = self.get_current_terms(n, 1, -1)
                outgoing = self.get_current_terms(n, 0, +1)

                terms = incoming + outgoing

                equations.append(Equation(self.get_current_source_total(n), terms))

        for b in self.batteries:
            equations.append(Equation(b.value, [
                Term(-1, UnknownVoltage(b.n0)),
                Term(1, UnknownVoltage(b.n1))
            ]))

        return equations


    def get_unknown_currents(self) -> list:
        unknown_currents = []

        for b in self.batteries:
            unknown_currents.append(UnknownCurrent(b))

        return unknown_currents


    def solve(self):
        equations = self.get_equations()
        unknown_currents = self.get_unknown_currents()
        unknown_voltages = list(map(lambda comp: UnknownVoltage(comp), self.nodes))

        print("Equations: ", [str(x) for x in equations])
        print("Unknown Currents: ", [str(x) for x in unknown_currents])
        print("Unknown Voltages: ", [str(x) for x in unknown_voltages])

        unknowns: list = unknown_currents + unknown_voltages

        print("All Unknown Variables: ", [str(x) for x in unknowns])

        A = np.zeros((len(equations), self.get_num_vars()), dtype=float)
        z = np.zeros((len(equations), 1), dtype=float)

        for row in range(len(equations)):
            print("\n\n")
            print(f"Stamp row {row} with node {row} equation {str(equations[row])}")
            equations[row].stamp(row, A, z, lambda comp: get_index_by_equals(unknowns, comp))

            print("A = ", A)
            print()
            print("z = ", z)
            print("\n\n")

        print("\nFinal:")
        print(A, "\n\n", z)

        try:
            x = np.linalg.solve(A, z)
        except np.linalg.LinAlgError:
            print("LinAlgError")
            x = np.zeros((len(equations), 1), dtype=float) # A.n, 1 original

        print("\nOut:\n")
        print(x)

        voltage_map = {}

        print("\nUnknown Voltages:")
        for v in unknown_voltages:
            voltage = x[get_index_by_equals(unknowns, v), 0]
            voltage_map[v.node] = voltage
            print(v.node, "=>", voltage)

        print("\nUnknown Currents:")
        for c in unknown_currents:
            c.element.current_solution = x[get_index_by_equals(unknowns, c), 0]
            print(c.element, c.element.current_solution)

        print("\nVoltage map:")
        print(voltage_map)

        return MNASolution(voltage_map, list(map(lambda comp: comp.element, unknown_currents)))

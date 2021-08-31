from math import fabs

from MNAElement import MNAElement

def num_approx_equals(a, b) -> bool:
    return fabs(a-b) < 1E-6

class MNASolution:
    def __init__(self, node_voltages: dict, elements: list):
        self.node_voltages: dict = node_voltages
        self.elements = elements

    def approx_equals(self, solution) -> bool:
        keys = self.node_voltages.keys()
        other_keys = solution.node_voltages.keys()

        key_difference = [x for x in keys if x not in other_keys]
        assert(len(key_difference) == 0)

        for k in keys:
            if not num_approx_equals(self.get_node_voltage(k), solution.get_node_voltage(k)):
                return False

        if not self.has_all_currents(solution):
            return False

        if not solution.has_all_currents(self):
            return False

        return True

    def has_all_currents(self, solution):
        for e in solution.elements:
            if not self.has_matching_element(e):
                return False
        return True

    def has_matching_element(self, element):
        for e in self.elements:
            if e.n0 == element.n0 and e.n1 == element.n1 and num_approx_equals(e.current_solution, element.current_solution):
                return True

        return False

    def get_current_for_resistor(self, resistor: MNAElement):
        v = - self.get_voltage(resistor)
        r = resistor.value
        i = v / r

        return i

    def get_node_voltage(self, node_index):
        return self.node_voltages[node_index]

    def get_voltage(self, element: MNAElement):
        return self.node_voltages[element.n1] - self.node_voltages[element.n0]

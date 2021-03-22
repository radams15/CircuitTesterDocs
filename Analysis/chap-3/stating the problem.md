# Stating the problem


## The problem

GCSE physics students in DGSB require knowledge of circuits as part of their
course, but unfortunately the physical equipment to teach many of these circuits
is expensive, limited in the school, is easily broken, and home learning
is not possible as equipment cannot be taken outside of school. Most students
simply learn about these circuits from an image in a textbook.

---
## The solution

A circuit simulator program that demonstrates
simple electrical circuits to determine if they will work, and allows students
to check if they function correctly would be an ideal solution.

The program would show current split, resistance
over distance, voltages, etc, as this is not possible inside school with
their present equipment.

The program is perfect for this problem as it is:

 - Cheaper to make than to purchase new circuit equipment
 - There are no user limits, so can be freely distributed to as many students as
	possible (even on devices at home), 
 - It is difficult to break as bugs can be easily fixed if identified.

This program would allow students to experiment with circuits at home as well,
as usually students cannot take equipment home because there is a limited amount,
and they are also quite delicate.

---
## Justification for computational solution

The physics calculations are an ideal fit for a computational solution.
This is because the amount of maths required is significant, so would be time-consuming for
anybody to do to just demonstrate the physics.

These calculations are not required by GCSE
level physics, so would be difficult to be shown manually by a teacher who does not need to
know or explain the equations. Showing the values of current and voltage at any point is
sufficient at GCSE level.

There will be a high level of abstraction, inheritance and polymorphism, as this
is needed for a hierarchy of components, with one base component extending off into a dozen
other components.

---
## Stakeholders

I will have two stakeholders, who will guide my progress throughout the project:

<br>

<table>
	<tr>
		<th>Persona</th>
		<th>Name(s)</th>
		<th>Requirements</th>
		<th>Availability</th>
	</tr>


	<tr>
		<td>Physics Teachers</td>
		<td style="color:red"><i>To Be Decided <br> (Will ask in person next week)</i></td>
		<td>
			<ul>
				<li>Input circuits from textbook</li>
				<li>Display on large whiteboard</li>
				<li>Save circuits to send students to experiment with/fix at home</li>
				<li>Show the current/voltage at each point of the circuit</li>
			</ul>
		</td>
		<td>Weekly</td>
		</tr>

	<tr>
		<td>Physics Students</td>
		<td>
			<li>My Sister (GCSE)</li>
			<li>My school peers (A-Level)</li>
		</td>
		<td>
			<ul>
				<li>Load Circuits emailed by teacher</li>
				<li>Save circuits for revision purposes</li>
				<li>Diagnose problems with circuits</li>
			</ul>
		</td>
		<td>Daily</td>
	</tr>
</table>

---
